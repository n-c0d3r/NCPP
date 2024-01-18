#include <ncpp/pac/thread_index.hpp>



namespace ncpp {

    namespace pac {

        namespace internal {

            thread_local u32 thread_index_g = 0;

        }



        void bind_thread_index(u32 i){

            internal::thread_index_g = i;
        }
        u32 thread_index(){

            return internal::thread_index_g;
        }

    }

}
