#pragma once

/**
 *  @file ncpp/pac/semaphore.hpp
 *  @brief Implementing semaphore.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>



namespace ncpp {
	
	namespace pac {
	
		/**
		 *	Implementing semaphore
		 */
        template <typename Mutex, typename CondVar>
        class semaphore_t {
        public:
            using native_handle_type = typename CondVar::native_handle_type;

            explicit semaphore_t(size_t count = 0);
            semaphore_t(const semaphore_t&) = delete;
            semaphore_t(semaphore_t&&) = delete;
            semaphore_t& operator=(const semaphore_t&) = delete;
            semaphore_t& operator=(semaphore_t&&) = delete;

            void notify();
            void wait();
            bool try_wait();
            template<class Rep, class Period>
            bool wait_for(const std::chrono::duration<Rep, Period>& d);
            template<class Clock, class Duration>
            bool wait_until(const std::chrono::time_point<Clock, Duration>& t);

            native_handle_type native_handle();

        private:
            Mutex   mMutex;
            CondVar mCv;
            size_t  mCount;
        };

        using semaphore = semaphore_t<std::mutex, std::condition_variable>;

        template <typename Mutex, typename CondVar>
        semaphore_t<Mutex, CondVar>::semaphore_t(size_t count)
            : mCount{count}
        {}

        template <typename Mutex, typename CondVar>
        void semaphore_t<Mutex, CondVar>::notify() {
            std::lock_guard<Mutex> lock{mMutex};
            ++mCount;
            mCv.notify_one();
        }

        template <typename Mutex, typename CondVar>
        void semaphore_t<Mutex, CondVar>::wait() {
            std::unique_lock<Mutex> lock{mMutex};
            mCv.wait(lock, [&]{ return mCount > 0; });
            --mCount;
        }

        template <typename Mutex, typename CondVar>
        bool semaphore_t<Mutex, CondVar>::try_wait() {
            std::lock_guard<Mutex> lock{mMutex};

            if (mCount > 0) {
                --mCount;
                return true;
            }

            return false;
        }

        template <typename Mutex, typename CondVar>
        template<class Rep, class Period>
        bool semaphore_t<Mutex, CondVar>::wait_for(const std::chrono::duration<Rep, Period>& d) {
            std::unique_lock<Mutex> lock{mMutex};
            auto finished = mCv.wait_for(lock, d, [&]{ return mCount > 0; });

            if (finished)
                --mCount;

            return finished;
        }

        template <typename Mutex, typename CondVar>
        template<class Clock, class Duration>
        bool semaphore_t<Mutex, CondVar>::wait_until(const std::chrono::time_point<Clock, Duration>& t) {
            std::unique_lock<Mutex> lock{mMutex};
            auto finished = mCv.wait_until(lock, t, [&]{ return mCount > 0; });

            if (finished)
                --mCount;

            return finished;
        }

        template <typename Mutex, typename CondVar>
        typename semaphore_t<Mutex, CondVar>::native_handle_type semaphore_t<Mutex, CondVar>::native_handle() {
            return mCv.native_handle();
        }
	
	} 

}