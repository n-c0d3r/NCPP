#pragma once

/**
 *  @file ncpp/utilities/native_smart_pointer.hpp
 *  @brief Implements native smart pointers.
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

#include <ncpp/utilities/smart_pointer.hpp>

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



        template<typename class__>
        using native_allocator_delete_t = allocator_deleter_t<native_allocator_t<class__>>;



        template<typename class__>
        using native_unique_ptr_t = std::unique_ptr<class__, native_allocator_delete_t<class__>>;

        template<typename class__, typename... arg_types__>
        inline native_unique_ptr_t<class__> native_allocate_unique_t(arg_types__&&... args) {

            return allocate_unique_t<class__, native_allocator_t<class__>, arg_types__...>(native_allocator_t<class__>(), std::forward<arg_types__>(args)...);
        }

        template<typename to_type__, typename from_type__>
        inline native_unique_ptr_t<to_type__> native_unique_ptr_cast_t(native_unique_ptr_t<from_type__>& unique_ptr) {

            return native_unique_ptr_t<to_type__>(static_cast<to_type__*>(unique_ptr.release()));
        }



        template<typename class__>
        using native_shared_ptr_t = std::shared_ptr<class__>;

        template<typename class__, typename... arg_types__>
        inline native_shared_ptr_t<class__> native_allocate_shared_t(arg_types__&&... args) {

            return std::allocate_shared<class__, native_allocator_t<class__>>(native_allocator_t<class__>(), std::forward<arg_types__>(args)...);
        }

        template<typename to_type__, typename from_type__>
        inline native_shared_ptr_t<to_type__> native_shared_ptr_cast_t(native_shared_ptr_t<from_type__> const & shared_ptr) {

            return std::static_pointer_cast<to_type__>(shared_ptr);
        }



        template<typename item_type__>
        std::ostream& operator << (std::ostream& os, const native_unique_ptr_t<item_type__>& ptr)
        {

            os << *ptr;

            return os;
        }

        template<typename item_type__>
        std::ostream& operator << (std::ostream& os, const native_shared_ptr_t<item_type__>& ptr)
        {

            os << *ptr;

            return os;
        }

    }

}