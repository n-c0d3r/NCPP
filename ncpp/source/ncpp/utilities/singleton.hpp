#pragma once

/**
 *  @file ncpp/utilities/singleton.hpp
 *  @brief Implements Singleton Pattern.
 */



#include <ncpp/prerequisites.hpp>



namespace ncpp {

    namespace utilities {

        /**
         *  Singleton template. Only allow 1 instance at a time.
         */
        template<class class__>
        class NCPP_DEFAULT_ALIGNAS singleton_t {

        private:
            static class__* instance_ps;/**< instance pointer. */



        public:
            static inline class__& instance() { return *instance_ps; }/**< use to get the instance reference. */



        protected:
            singleton_t() {

                assert(instance_ps == 0 && "only accept 1 instance at a time!");

                instance_ps = (class__*)this;

            }

        public:
            ~singleton_t() {

                instance_ps = 0;

            }

            singleton_t(const singleton_t&) = delete;
            singleton_t& operator = (const singleton_t&) = delete;
            singleton_t(singleton_t&&) = delete;
            singleton_t& operator = (singleton_t&&) = delete;

        };

        template<class class__>
        class__* singleton_t<class__>::instance_ps = 0;

    }

}