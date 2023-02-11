#pragma once

/**
 *  @file ncpp/dop/cbjs.hpp
 *  @brief Implements coroutine based job system.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>
#include <ncpp/containers/.hpp>
#include <ncpp/pac/.hpp>



namespace ncpp {

	namespace dop {

		struct job;
		class job_coroutine;
		class cbjs;
		class worker_thread;


		
		enum class job_priority {

			HIGH = 0,
			NORMAL = 1,
			LOW = 2

		};
		
		struct NCPP_DEFAULT_ALIGNAS job {

			std::function<void(job_coroutine&)> entry_point;
			job_priority priority;

		};



		template<typename data_type__>
		using cbjs_allocator_t = typename ncpp::tgh_allocator_t<data_type__, tagged_heap_t<>>;

		template<typename data_type__>
		using cbjs_unique_ptr_t = typename std::unique_ptr<data_type__, typename utilities::allocator_deleter_t<typename cbjs_allocator_t<data_type__>>>;



		class NCPP_DEFAULT_ALIGNAS job_coroutine {

#pragma region Properties
		private:
			/**
			 *  The job to be run.
			 */
			dop::job* job_p_;

			/**
			 *  The fiber to implement a function that can suspend execution to be resumed later.
			 */
			pac::fiber fiber_;
#pragma endregion



#pragma region Getters and Setters
		public:
			inline dop::job& job() const { return *job_p_; }
#pragma endregion



#pragma region Constructors, Destructor and Operators
		public:
			/**
			 *  Default constructor
			 */
			inline job_coroutine() :
				job_p_(0),
				fiber_(
					pac::fiber_creation_mode::NEW,
					[&](pac::fiber& fiber) {

						worker_loop();

					}
				)
			{



			}
			/**
			 *  Destructor
			 */
			~job_coroutine() {



			}
#pragma endregion



#pragma region Methods
		private:
			void worker_loop();


		public:
			/**
			 *  Binds the job to run in the next time "switch_to_this" called
			 */
			inline void bind_job(dop::job& j) {

				job_p_ = &j;

			}

			/**
			 *  Switches from the current thread's fiber to this fiber
			 */
			inline void switch_to_this() {

				fiber_.switch_to_this();

			}
#pragma endregion

		};



		/**
		 *  A worker thread is a thread working in the job system.
		 */
		class NCPP_DEFAULT_ALIGNAS worker_thread {

#pragma region Properties
		private:
			u8 index_;
#pragma endregion



#pragma region Getters and Setters
		public:
			inline u8 index() const { return index_; }
#pragma endregion



#pragma region Constructors, Destructor and Operators
		public:
			/**
			 *  Default constructor
			 */
			worker_thread(u8 index);
			/**
			 *  Destructor
			 */
			~worker_thread() {



			}
#pragma endregion



#pragma region Methods

#pragma endregion

		};



		/**
		 *  Specifies which job need to be run first and how job system could run.
		 */
		struct NCPP_DEFAULT_ALIGNAS cbjs_settings {

			job& entry_job;
			u8 worker_thread_count;

		};



		/**
		 *  The main class of coroutine based job system
		 */
		class NCPP_DEFAULT_ALIGNAS cbjs {

#pragma region Typedefs
		public:
			using worker_thread_ptr_type = typename cbjs_unique_ptr_t<worker_thread>;
			using worker_thread_allocator_type = typename cbjs_allocator_t<worker_thread>;
			using worker_thread_ptr_allocator_type = typename cbjs_allocator_t<worker_thread_ptr_type>;
			using worker_thread_ptr_vector_type = typename std::vector<worker_thread_ptr_type, worker_thread_ptr_allocator_type>;
#pragma endregion



#pragma region Properties
		private:
			cbjs_settings settings_;

			tagged_heap_t<> tagged_heap_;
			tagged_heap_t<>::category_id_type tgh_forever_cid_;

			worker_thread_allocator_type worker_thread_allocator_;
			worker_thread_ptr_allocator_type worker_thread_ptr_allocator_;
			worker_thread_ptr_vector_type worker_thread_ptr_vector_;
#pragma endregion



#pragma region Getters and Setters
		public:
			inline cbjs_settings settings() const { return settings_; }

			inline tagged_heap_t<>& tagged_heap() { return tagged_heap_; }
			inline const tagged_heap_t<>& tagged_heap() const { return tagged_heap_; }

			inline tagged_heap_t<>::category_id_type tgh_forever_cid() const { return tgh_forever_cid_; }

			inline worker_thread& get_worker_thread(u8 index) { return *worker_thread_ptr_vector_[index]; }
			inline const worker_thread& get_worker_thread(u8 index) const { return *worker_thread_ptr_vector_[index]; }
#pragma endregion



#pragma region Constructors, Destructor and Operators
		public:
			/**
			 *  Default constructor
			 */
			inline cbjs(const cbjs_settings& settings) :
				settings_(settings),

				tagged_heap_(16),
				tgh_forever_cid_(tagged_heap_.create_category()),

				worker_thread_allocator_(tagged_heap_, tgh_forever_cid_),
				worker_thread_ptr_allocator_(tagged_heap_, tgh_forever_cid_),
				worker_thread_ptr_vector_(settings.worker_thread_count, worker_thread_ptr_allocator_)
			{



			}
			/**
			 *  Destructor
			 */
			~cbjs() {



			}
#pragma endregion



#pragma region Methods

#pragma endregion

		};

	}

}