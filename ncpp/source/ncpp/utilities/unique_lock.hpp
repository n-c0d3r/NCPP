#pragma once

/**
 *  @file ncpp/utilities/unique_lock.hpp
 *  @brief Implements unique_lock_t.
 */



#include <ncpp/prerequisites.hpp>



namespace ncpp {

    namespace utilities {

        /**
         *  An object that manages a mutex object by keeping it always locked.
         */
        template<class locker_class__>
        class NCPP_DEFAULT_SET_ALIGN unique_lock_t {

        private:
            locker_class__& locker_;



        public:
            inline locker_class__& locker() { return locker_; }
            inline const locker_class__& locker() const { return locker_; }



        public:
            unique_lock_t(locker_class__& locker) :
                locker_(locker)
            {

                locker_.lock();

            }
            ~unique_lock_t() {

                locker_.unlock();

            }

        };

    }

}