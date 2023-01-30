#pragma once


namespace ncpp {

	template<class _class>
    class NCPP_DEFAULT_ALIGN singleton_t {

    private:
        static _class* instance_ps;



    public:
        static NCPP_GETTER(_class* instance()) { return instance_ps; }



    protected:
        singleton_t()
        {

            instance_ps = (_class*)this;

        }



    public:
        template<typename... arg_types>
        static NCPP_CONSTEXPR _class* create_instance_t(arg_types... args) {

            return new _class(std::forward<arg_types>(args)...);
        }
        static inline void release_instance() {

            delete instance_ps;
        }

    };

    template<class _class>
    _class* singleton_t<_class>::instance_ps = 0;



    template<class _class>
    class NCPP_DEFAULT_ALIGN protected_singleton_t {

    private:
        static _class* instance_ps;



    public:
        static NCPP_GETTER(_class* instance_p()) { return instance_ps; }



    protected:
        protected_singleton_t()
        {

            instance_ps = (_class*)this;

        }



    protected:
        template<typename... arg_types>
        static NCPP_CONSTEXPR _class* create_instance_t(arg_types... args) {

            return new _class(std::forward<arg_types>(args)...);
        }
        static inline void release_instance() {

            delete instance_ps;
        }

    };

    template<class _class>
    _class* protected_singleton_t<_class>::instance_ps = 0;

}