#pragma once

#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>
#include <ncpp/containers/.hpp>
#include <ncpp/pac/.hpp>
#include <ncpp/cbjs/.hpp>

#include <ncpp/ecs/system.hpp>



namespace ncpp {

	namespace ecs {

        template<typename data_type, template<typename data_type> class allocator_t = std::allocator>
        class NCPP_DEFAULT_SET_ALIGN component_system_t :
            public system_it<data_type, allocator_t>
        {

        public:
            component_system_t(sz reserve_count, sz thread_count) :
                system_it(reserve_count, thread_count)
            {



            }
            virtual ~component_system_t() {



            }

        };

	}

}