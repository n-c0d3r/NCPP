#pragma once


namespace ncpp {

	template<class lock_class>
    class NCPP_DEFAULT_ALIGN lock_guard_t {

    private:
        lock_class& lock_;



    public:
        NCPP_GETTER(lock_class& lock()) { return lock_; }
        NCPP_GETTER(const lock_class& lock()) const { return lock_; }



    public:
        inline lock_guard_t(lock_class& lock) :
            lock_(lock)
        {

            lock_.lock();

        }
        ~lock_guard_t(){

            lock_.unlock();

        }

    };

}