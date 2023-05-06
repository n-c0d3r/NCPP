#pragma once

/**
 *  @file ncpp/rtti/rclass.hpp
 *  @brief Implements reflected class.
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

#include <ncpp/utilities/.hpp>
#include <ncpp/containers/.hpp>
#include <ncpp/dop/.hpp>
#include <ncpp/pac/.hpp>

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

    namespace rtti {

        class robject_i;
        template<
            class object_type__
        >
        class robject_t;



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        enum class rclass_create_mode {

            DEFAULT = 0,
            SHARED = 1,
            UNIQUE = 2

        };



        /**
         *  Reflected class template.
         */
        template<class object_type__>
        class rclass_t final
        {

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            using create_instance_func_ptr_type = void (*)(void* class_p, void* output_p, rclass_create_mode create_mode);

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        protected:
            create_instance_func_ptr_type create_instance_func_ptr_;

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            inline const create_instance_func_ptr_type& create_instance_func_ptr() const { return create_instance_func_ptr_; };

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

#pragma region Constructors, Destructor and Operators
        public:
            inline rclass_t() :
                create_instance_func_ptr_(0)
            {

                reset();

            }
            ~rclass_t() {



            }



            inline rclass_t(const rclass_t& other) :
                create_instance_func_ptr_(
                    other.create_instance_func_ptr_
                )
            {



            }
            inline rclass_t& operator = (const rclass_t& other)
            {

                create_instance_func_ptr_ = other.create_instance_func_ptr_;

                return *this;
            }

            inline rclass_t(rclass_t&& other) :
                create_instance_func_ptr_(
                    std::move(other.create_instance_func_ptr_)
                )
            {

                other.reset();

            }
            inline rclass_t& operator = (rclass_t&& other)
            {

                create_instance_func_ptr_ = std::move(other.create_instance_func_ptr_);

                other.reset();

                return *this;
            }



            template<typename other_object_type__>
            inline rclass_t(const rclass_t<other_object_type__>& other) :
                create_instance_func_ptr_(
                    other.create_instance_func_ptr()
                )
            {

                static_assert(is_convertible_t<other_object_type__>() && "other object type is not base of object type");

            }
            template<typename other_object_type__>
            inline rclass_t& operator = (const rclass_t<other_object_type__>& other)
            {

                static_assert(is_convertible_t<other_object_type__>() && "other object type is not base of object type");

                create_instance_func_ptr_ = other.create_instance_func_ptr();

                return *this;
            }

            template<typename other_object_type__>
            inline rclass_t(rclass_t<other_object_type__>&& other) :
                create_instance_func_ptr_(
                    std::move(other.create_instance_func_ptr())
                )
            {

                static_assert(is_convertible_t<other_object_type__>() && "other object type is not base of object type");

                other.reset();

            }
            template<typename other_object_type__>
            inline rclass_t& operator = (rclass_t<other_object_type__>&& other)
            {

                static_assert(is_convertible_t<other_object_type__>() && "other object type is not base of object type");

                create_instance_func_ptr_ = std::move(other.create_instance_func_ptr());

                other.reset();

                return *this;
            }
#pragma endregion

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

#pragma region Methods
        public:
            inline object_type__& create_instance() {

                object_type__* result;

                create_instance_func_ptr_(this, &result, rclass_create_mode::DEFAULT);

                return *result;
            }
            inline utilities::native_shared_ptr_t<object_type__> create_shared_instance() {

                utilities::native_shared_ptr_t<object_type__> result;

                create_instance_func_ptr_(this, &result, rclass_create_mode::SHARED);

                return result;
            }
            inline utilities::native_unique_ptr_t<object_type__> create_unique_instance() {

                utilities::native_unique_ptr_t<object_type__> result;

                create_instance_func_ptr_(this, &result, rclass_create_mode::UNIQUE);

                return std::move(result);
            }

            inline void reset() {

                create_instance_func_ptr_ = [](void* class_p, void* output_p, rclass_create_mode create_mode) -> void {

                    switch (create_mode)
                    {
                    case ncpp::rtti::rclass_create_mode::DEFAULT:
                        *((object_type__**)output_p) = native_new_t<object_type__>();
                        break;
                    case ncpp::rtti::rclass_create_mode::SHARED:
                        *((utilities::native_shared_ptr_t<object_type__>*)output_p) = utilities::native_allocate_shared_t<object_type__>();
                        break;
                    case ncpp::rtti::rclass_create_mode::UNIQUE:
                        *((utilities::native_unique_ptr_t<object_type__>*)output_p) = utilities::native_allocate_unique_t<object_type__>();
                        break;
                    default:
                        break;
                    }
                    
                };

            }

            template<typename other_object_type__>
            static inline constexpr b8 is_convertible_t() {

                return (
                    utilities::is_derived_from_t<other_object_type__, object_type__>()
                    || utilities::is_derived_from_t<object_type__, other_object_type__>()
                );
            }
#pragma endregion

        };

    }

}