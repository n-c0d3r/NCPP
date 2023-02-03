#pragma once

#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>
#include <ncpp/containers/.hpp>
#include <ncpp/pac/.hpp>
#include <ncpp/cbjs/.hpp>



namespace ncpp {
	
	namespace ecs {
	
        template<typename data_type, template<typename data_type> class allocator_t = std::allocator>
        class system_it 
        {

        protected:
            system_it(sz reserve_count) {



            }
            ~system_it() {



            }


        };



        template<typename data_type>
        using standard_system_it = typename system_it<data_type, std::allocator>;
	
	} 

}