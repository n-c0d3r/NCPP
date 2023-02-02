#pragma once

/**
 *  @file ncpp/utilities/singleton.hpp
 *  @brief Implementing Singleton Pattern.
 */



#include <ncpp/prerequisites.hpp>



namespace ncpp {

    namespace utilities {

        /**
         *  Singleton template. Only allow 1 instance at a time.
         */
        template<class _class>
        class NCPP_DEFAULT_ALIGN singleton_t {

        private:
            static _class* instance_ps;/**< instance pointer. */



        public:
            static inline _class& instance() { return *instance_ps; }/**< use to get the instance reference. */



        protected:
            singleton_t() {

                assert(instance_ps == 0 && "only accept 1 instance at a time!");

                instance_ps = (_class*)this;

            }
            ~singleton_t() {

                instance_ps = 0;

            }

        };

        template<class _class>
        _class* singleton_t<_class>::instance_ps = 0;

    }

}