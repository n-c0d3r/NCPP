#pragma once

#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>
#include <ncpp/containers/.hpp>
#include <ncpp/pac/.hpp>
#include <ncpp/cbjs/.hpp>



namespace ncpp {
	
	namespace ecs {
	
        template<typename data_type, template<typename data_type> class allocator_t = std::allocator>
        class NCPP_DEFAULT_SET_ALIGN system_it 
        {



        protected:
            inline system_it(sz reserve_count, sz thread_count)
            {



            }

        public:
            virtual ~system_it() {



            }

        };
	
	} 

}