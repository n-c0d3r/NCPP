#pragma once

/**
 *  @file ncpp/utilities/lock_guard.hpp
 *  @brief Implementing lock_guard_t.
 */



#include <ncpp/prerequisites.hpp>



namespace ncpp {

    namespace utilities {

        /**
         *  An object that manages a mutex object by keeping it always locked.
         */
        template<class locker_class>
        class NCPP_DEFAULT_ALIGN lock_guard_t {

        private:
            locker_class& locker_;



        public:
            inline locker_class& locker() { return locker_; }
            inline const locker_class& locker() const { return locker_; }



        public:
            lock_guard_t(locker_class& locker) :
                locker_(locker)
            {

                locker_.lock();

            }
            ~lock_guard_t() {

                locker_.unlock();

            }

        };

    }

}