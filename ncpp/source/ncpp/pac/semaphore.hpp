#pragma once

/**
 *  @file ncpp/pac/semaphore.hpp
 *  @brief Implements semaphore.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>



namespace ncpp {
	
	namespace pac {
	
		/**
		 *	Implements semaphore
		 */
        template <typename mutex_type__, typename cond_var__>
        class NCPP_DEFAULT_SET_ALIGN semaphore_t {
        public:
            using native_handle_type = typename cond_var__::native_handle_type;

            explicit semaphore_t(sz count = 0);
            semaphore_t(const semaphore_t&) = delete;
            semaphore_t(semaphore_t&&) = delete;
            semaphore_t& operator=(const semaphore_t&) = delete;
            semaphore_t& operator=(semaphore_t&&) = delete;

            void notify();
            void wait();
            b8 try_wait();
            template<class rep__, class period__>
            b8 wait_for(const std::chrono::duration<rep__, period__>& d);
            template<class clock__, class duration__>
            b8 wait_until(const std::chrono::time_point<clock__, duration__>& t);

            native_handle_type native_handle();

        private:
            mutex_type__   mutex_;
            cond_var__ cv_;
            sz  count__;
        };

        using semaphore = semaphore_t<std::mutex, std::condition_variable>;

        template <typename mutex_type__, typename cond_var__>
        semaphore_t<mutex_type__, cond_var__>::semaphore_t(sz count)
            : count__{count}
        {}

        template <typename mutex_type__, typename cond_var__>
        void semaphore_t<mutex_type__, cond_var__>::notify() {
            std::lock_guard<mutex_type__> lock{mutex_};
            ++count__;
            cv_.notify_one();
        }

        template <typename mutex_type__, typename cond_var__>
        void semaphore_t<mutex_type__, cond_var__>::wait() {
            std::unique_lock<mutex_type__> lock{mutex_};
            cv_.wait(lock, [&]{ return count__ > 0; });
            --count__;
        }

        template <typename mutex_type__, typename cond_var__>
        b8 semaphore_t<mutex_type__, cond_var__>::try_wait() {
            std::lock_guard<mutex_type__> lock{mutex_};

            if (count__ > 0) {
                --count__;
                return true;
            }

            return false;
        }

        template <typename mutex_type__, typename cond_var__>
        template<class rep__, class period__>
        b8 semaphore_t<mutex_type__, cond_var__>::wait_for(const std::chrono::duration<rep__, period__>& d) {
            std::unique_lock<mutex_type__> lock{mutex_};
            auto finished = cv_.wait_for(lock, d, [&]{ return count__ > 0; });

            if (finished)
                --count__;

            return finished;
        }

        template <typename mutex_type__, typename cond_var__>
        template<class clock__, class duration__>
        b8 semaphore_t<mutex_type__, cond_var__>::wait_until(const std::chrono::time_point<clock__, duration__>& t) {
            std::unique_lock<mutex_type__> lock{mutex_};
            auto finished = cv_.wait_until(lock, t, [&]{ return count__ > 0; });

            if (finished)
                --count__;

            return finished;
        }

        template <typename mutex_type__, typename cond_var__>
        typename semaphore_t<mutex_type__, cond_var__>::native_handle_type semaphore_t<mutex_type__, cond_var__>::native_handle() {
            return cv_.native_handle();
        }
	
	} 

}