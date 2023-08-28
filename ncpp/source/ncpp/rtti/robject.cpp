
#include <ncpp/.hpp>
#include <ncpp/rtti/robject.hpp>



namespace ncpp {

	namespace rtti {



#ifdef NCPP_ENABLE_RTTI
		thread_local rcontext_base* current_context_p_g = 0;



		reflector_container_base::reflector_container_base(rcontext_base& context) {

			current_context_p_g = &context;

		}

		void reflector_container_base::apply_name(rcontext_base& context, const eastl::string& name) {

			context.name_ = name;

		}
		void reflector_container_base::apply_hash_code(rcontext_base& context, sz hash_code) {

			context.hash_code_ = hash_code;

		}



		rcontext_base& current_context() {

			return *current_context_p_g;
		}
#endif

	}

}