#pragma once

#include <ncpp/prerequisites.hpp>



namespace ncpp {

    namespace utilities {

        template<class _class>
        class NCPP_DEFAULT_ALIGN singleton_t {

        private:
            static _class* instance_ps;



        public:
            static _class& instance() { return *instance_ps; }



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