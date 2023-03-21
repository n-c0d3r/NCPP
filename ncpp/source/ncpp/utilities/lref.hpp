#pragma once

/**
 *  @file ncpp/utilities/lref.hpp
 *  @brief Implements lvalue reference.
 */



 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma region Includes

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/prerequisites.hpp>

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/utilities/nth_template_arg.hpp>

#pragma endregion



 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



namespace ncpp {

    namespace utilities {



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        /**
         *  non-atomic lvalue reference template.
         */
        template<class type__>
        class na_lref_t {

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        private:
            type__* raw_pointer_;/**< raw pointer. */

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            inline type__& get() { return *raw_pointer_; }/**< uses to get the object. */
            inline const type__& get() const { return *raw_pointer_; }/**< uses to get the object. */
            inline void set(const type__& value) { *raw_pointer_ = value; }
            inline void set(type__&& value) { *raw_pointer_ = std::move(value); }
            inline b8 is_null() const { return raw_pointer_ == 0; }/**< checks if the raw pointer is null. */
            inline type__* pointer() { return raw_pointer_; }
            inline const type__* pointer() const { return raw_pointer_; }

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            inline na_lref_t() noexcept :
                raw_pointer_(0)
            {



            }
            inline na_lref_t(type__& raw_ref) noexcept :
                raw_pointer_(&raw_ref)
            { 



            }
            inline na_lref_t(const type__& raw_ref) noexcept :
                raw_pointer_((type__*)&raw_ref)
            {



            }
            inline na_lref_t(type__&& raw_ref) noexcept :
                raw_pointer_(&raw_ref)
            {

                static_assert(false && "cant reference to rvalue.");

            }
            ~na_lref_t() {

            }

            inline na_lref_t(const na_lref_t& other) noexcept :
                raw_pointer_(other.raw_pointer_)
            {
            }
            inline na_lref_t& operator = (const na_lref_t& other) noexcept {
                
                raw_pointer_ = other.raw_pointer_;

                return *this;
            }
            inline na_lref_t& operator = (const type__& other) noexcept {

                raw_pointer_ = (type__*)(&other);

                return *this;
            }
            inline na_lref_t(na_lref_t&& other) noexcept :
                raw_pointer_(other.raw_pointer_)
            {

                other.raw_pointer_ = 0;

            }
            inline na_lref_t& operator = (na_lref_t&& other) noexcept {
                
                raw_pointer_ = other.raw_pointer_;
                other.raw_pointer_ = 0;

                return *this;
            }
            inline b8 operator == (const na_lref_t& other) const noexcept {

                return other.raw_pointer_ == raw_pointer_;
            }
            inline b8 operator == (const type__& other) const noexcept {

                return other.raw_pointer_ == &raw_pointer_;
            }
            inline b8 operator != (const na_lref_t& other) const noexcept {

                return other.raw_pointer_ != raw_pointer_;
            }
            inline b8 operator != (const type__& other) const noexcept {

                return other.raw_pointer_ != &raw_pointer_;
            }

            inline type__* operator -> () {

                return raw_pointer_;
            }
            inline const type__* operator -> () const {

                return raw_pointer_;
            }

            inline type__& operator * () {

                return *raw_pointer_;
            }
            inline const type__& operator * () const {

                return *raw_pointer_;
            }

        };



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        /**
         *  atomic lvalue reference template.
         */
        template<class type__>
        class a_lref_t {

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        private:
            std::atomic<type__*> aptr_;/**< unsigned int pointer. */

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            inline type__& get() { return *aptr_.load(std::memory_order_acquire); }/**< uses to get the object. */
            inline const type__& get() const { return *aptr_.load(std::memory_order_acquire); }/**< uses to get the object. */
            inline void set(const type__& value) { *(aptr_.load(std::memory_order_acquire)) = value; }
            inline void set(type__&& value) { *(aptr_.load(std::memory_order_acquire)) = std::move(value); }
            inline type__* pointer() { return aptr_.load(std::memory_order_acquire); }
            inline const type__* pointer() const  { return aptr_.load(std::memory_order_acquire); }
            inline b8 is_null() const { return aptr_.load(std::memory_order_acquire) == 0; }/**< checks if the pointer is null. */

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            inline a_lref_t() noexcept :
                aptr_(0)
            {



            }
            inline a_lref_t(type__& raw_ref) noexcept :
                aptr_(&raw_ref)
            {



            }
            inline a_lref_t(const type__& raw_ref) noexcept :
                aptr_((type__*)&raw_ref)
            {



            }
            inline a_lref_t(type__&& raw_ref) noexcept :
                aptr_(&raw_ref)
            {

                static_assert(false && "cant reference to rvalue.");

            }
            ~a_lref_t() {

            }

            inline a_lref_t(const a_lref_t& other) noexcept :
                aptr_(other.aptr_.load(std::memory_order_acquire))
            {
            }
            inline a_lref_t& operator = (const a_lref_t& other) noexcept {

                std::atomic_thread_fence(std::memory_order_release);

                aptr_.store(other.aptr_.load(std::memory_order_acquire), std::memory_order_relaxed);

                return *this;
            }
            inline a_lref_t& operator = (const type__& other) noexcept {

                std::atomic_thread_fence(std::memory_order_release);

                aptr_.store((type__*)&other, std::memory_order_relaxed);

                return *this;
            }
            inline a_lref_t(a_lref_t&& other) noexcept :
                aptr_(other.aptr_.load(std::memory_order_acquire))
            {

                other.aptr_.store(0, std::memory_order_release);

            }
            inline a_lref_t& operator = (a_lref_t&& other) noexcept {

                std::atomic_thread_fence(std::memory_order_release);

                aptr_.store(other.aptr_.load(std::memory_order_acquire), std::memory_order_relaxed);
                other.aptr_.store(0, std::memory_order_relaxed);

                return *this;
            }
            inline b8 operator == (const a_lref_t& other) const noexcept {

                return other.aptr_.load(std::memory_order_acquire) == (aptr_.load(std::memory_order_acquire));
            }
            inline b8 operator == (const type__& other) const noexcept {

                return &other != aptr_.load(std::memory_order_acquire);
            }
            inline b8 operator != (const a_lref_t& other) const noexcept {

                return other.aptr_.load(std::memory_order_acquire) != aptr_.load(std::memory_order_acquire);
            }
            inline b8 operator != (const type__& other) const noexcept {

                return &other != aptr_.load(std::memory_order_acquire);
            }

            inline type__* operator -> () {

                return (aptr_.load(std::memory_order_acquire));
            }
            inline const type__* operator -> () const {

                return (aptr_.load(std::memory_order_acquire));
            }
            inline type__& operator * () {

                return *(aptr_.load(std::memory_order_acquire));
            }
            inline const type__& operator * () const {

                return *(aptr_.load(std::memory_order_acquire));
            }

        };



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        /**
         *  lvalue reference template.
         */
        template<typename type__, b8 is_atomic__ = false>
        using lref_t = typename utilities::nth_template_arg_t<
            (sz)is_atomic__, 
            typename na_lref_t<type__>,
            typename a_lref_t<type__>
        >::type;

    }

}