#pragma once

/**
 *  @file ncpp/utilities/smart_pointer.hpp
 *  @brief Implements smart pointer functionalities.
 */



#include <ncpp/prerequisites.hpp>



namespace ncpp {

    namespace utilities {

        template<typename allocator_type__>
        struct allocator_deleter_t
        {
            allocator_type__ alloc_;
            allocator_deleter_t() {}
            allocator_deleter_t(const allocator_type__& a) : alloc_(a) { }

            template<typename class__>
            void operator()(class__* p)
            {
                p->~class__();
                alloc_.deallocate(p, 1);
            }
        };

        template<typename class__, typename allocator_type__, typename... Args>
        auto allocate_unique_t(const allocator_type__& alloc, Args&&... args)
        {
            using rebind = typename std::allocator_traits<allocator_type__>::template rebind_alloc<class__>;
            using deleter = allocator_deleter_t<rebind>;

            auto d = deleter { rebind { alloc } };
            auto* p = d.alloc_.allocate(1);
            try { p = new(p) class__ { std::forward<Args>(args)... }; }
            catch (...) { d.alloc_.deallocate(p, 1); throw; }

            return std::unique_ptr<class__, deleter>(p, d);
        }


    }

}