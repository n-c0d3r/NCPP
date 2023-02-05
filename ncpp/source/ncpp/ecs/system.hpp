#pragma once

#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>
#include <ncpp/containers/.hpp>
#include <ncpp/pac/.hpp>
#include <ncpp/cbjs/.hpp>



namespace ncpp {
	
	namespace ecs {
	
        template<typename data_type__, template<typename data_type__> class allocator_t__ = std::allocator>
        class NCPP_DEFAULT_SET_ALIGN system_it 
        {

#pragma region Typedefs
        public:
            using data_type = data_type__;

            using data_map_type = typename containers::handle_map_t<data_type, allocator_t__>;
            using processing_functor_type = std::function<void(cbjs::job& job, cbjs::coroutine& coroutine, u32 begin, u32 end)>;
            using id_type = typename data_map_type::id_type;
            using cell_type = typename data_map_type::cell_type;
#pragma endregion 



#pragma region Properties
        private:
            data_map_type map_;

            u32 thread_count_;

            std::array<cbjs::job, 128> job_array_;

            std::atomic_uint32_t swappable_;
            std::atomic_uint32_t last_size_;
            pac::spinlock insertion_spinlock_;
#pragma endregion 



#pragma region Getters and Setters
        public:
            inline data_map_type& map() { return map_; }
            inline const data_map_type& map() const { return map_; }

            inline u32 thread_count() const { return thread_count_; }
#pragma endregion 



#pragma region Constructors, Destructor and Operators
        protected:
            inline system_it(u32 thread_count, sz map_reserve_count) :
                map_(map_reserve_count),
                thread_count_(thread_count)
            {



            }

        public:
            virtual ~system_it() {



            }

            system_it(const system_it&) = delete;
            system_it& operator = (const system_it&) = delete;
            system_it(system_it&&) = delete;
            system_it& operator = (system_it&&) = delete;

            inline cell_type& operator [] (u32 index) {

                return at(index);
            }
            inline const cell_type& operator [] (u32 index) const {

                return at(index);
            }
#pragma endregion



#pragma region Methods
        private:
            template<typename passed_type__>
            inline id_type insert_main_t(passed_type__&& item) {

                utilities::unique_lock_t<pac::spinlock> lock_guard(insertion_spinlock_);

                return map_.insert(std::forward<passed_type__>(item));
            }

            inline void internal_process_data(cbjs::job& job, cbjs::coroutine& coroutine, u8 priority, u32 size, const processing_functor_type& fn) {
                wait(coroutine, async_internal_process_data(job, coroutine, priority, size, fn));
            }
            inline u32 async_internal_process_data(cbjs::job& job, cbjs::coroutine& coroutine, u8 priority, u32 size, const processing_functor_type& fn) {

                if (size == 0) return 0;

                u32 step = thread_step(size);
                u32 rtc = runnable_thread_count(size);
                u32 begin = 0;
                u32 end = size;

                u32 job_index = 0;

                while (begin < end) {

                    cbjs::job& t_job = job_array_[job_index];

                    t_job.reset();
                    t_job.priority = priority;
                    t_job.functor = [begin, step, end, fn](cbjs::job& job, cbjs::coroutine& coroutine) {

                        fn(job, coroutine, begin, min(begin + step, end));

                    };

                    ++job_index;
                    begin += step;
                }

                for (u32 i = 0; i < job_index; ++i) {

                    cbjs::system::instance().worker_thread(i).schedule(job_array_[i]);

                }

                return job_index;
            }



        public:
            inline void process_data(cbjs::job& job, cbjs::coroutine& coroutine, u8 priority, const processing_functor_type& fn) {
                wait(coroutine, async_process_data(job, coroutine, priority, fn));
            }
            inline u32 async_process_data(cbjs::job& job, cbjs::coroutine& coroutine, u8 priority, const processing_functor_type& fn) {

                std::atomic_thread_fence(std::memory_order_release);

                swappable_.store(map_.size(), std::memory_order_relaxed);
                last_size_.store(map_.size(), std::memory_order_relaxed);

                return async_internal_process_data(job, coroutine, priority, map_.size(), fn);
            }

            inline void recorrect_data(cbjs::job& job, cbjs::coroutine& coroutine, u8 priority) {
                wait(coroutine, async_recorrect_data(job, coroutine, priority));
            }
            inline u32 async_recorrect_data(cbjs::job& job, cbjs::coroutine& coroutine, u8 priority) {

                u32 last_size = last_size_.load(std::memory_order_relaxed);
                u32 swappable = swappable_.load(std::memory_order_relaxed);

                std::atomic_thread_fence(std::memory_order_acquire);

                u32 counter = async_internal_process_data(
                    job,
                    coroutine,
                    priority,
                    last_size - swappable,
                    [this, last_size, swappable](cbjs::job& job, cbjs::coroutine& coroutine, u32 begin, u32 end) {

                        auto& map = this->map();
                        auto& sparse_vector = map.sparse_vector();
                        auto& dense_vector = map.dense_vector();

                        for (u32 i = begin; i != end; ++i) {

                            u32 inner_index = swappable + i;

                            cell_type& cell = dense_vector.at(inner_index);

                            if (cell.inner_index != inner_index) {

                                id_type& id = sparse_vector.at(cell.outer_index);
                                id.inner_index = cell.inner_index;

                                std::swap(dense_vector[cell.inner_index], cell);

                            }

                        }

                    }
                );

                return counter;
            }

            inline void wait(cbjs::coroutine& coroutine, u32 counter) {

                for (u32 i = 0; i < counter; ++i) {

                    coroutine.yield(cbjs::wait_job_done(job_array_[i]));

                }

            }

            inline u32 thread_step(u32 size) {

                return size / thread_count_ + (size % thread_count_ > 0);
            }
            inline u32 runnable_thread_count(u32 size) {

                return size * (size < thread_count_) + (size >= thread_count_) * thread_count_;
            }

            inline cell_type& at(u32 index) {

                return map_[index];
            }
            inline const cell_type& at(u32 index) const {

                return map_[index];
            }

            inline id_type insert(const data_type& data) {

                return insert_main_t(std::forward<data_type&>(data));
            }
            inline id_type insert(data_type&& data) {

                return insert_main_t(std::forward<data_type>(data));
            }

            inline void thread_safe_erase(u32 inner_index) {

                u32 swappable_index = swappable_.load(std::memory_order_acquire);

                while(!swappable_.compare_exchange_weak(swappable_index, swappable_index - 1));

                --swappable_index;

                at(swappable_index).inner_index = inner_index;

            }
#pragma endregion

        };
	
	} 

}