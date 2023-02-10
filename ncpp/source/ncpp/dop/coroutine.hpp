#pragma once

/**
 *  @file ncpp/dop/cbjs.hpp
 *  @brief Implements coroutine based job system.
 */



#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>
#include <ncpp/containers/.hpp>
#include <ncpp/pac/.hpp>



namespace ncpp {

	namespace dop {

        struct NCPP_DEFAULT_ALIGNAS coroutine;
        struct NCPP_DEFAULT_ALIGNAS job;
        class NCPP_DEFAULT_ALIGNAS cbjs;
        class NCPP_DEFAULT_ALIGNAS worker_thread;



        /**
         *  A coroutine is a function that can suspend execution to be resumed later.
         */
        struct NCPP_DEFAULT_ALIGNAS coroutine {

#pragma region Properties
        private:
            /**
             *  The job to be run.
             */
            dop::job* job_p_;

            /**
             *  The fiber to implement a function that can suspend execution to be resumed later.
             */
            pac::fiber fiber_;
#pragma endregion



#pragma region Getters and Setters
        public:
            inline dop::job& job() const { return *job_p_; }
#pragma endregion



#pragma region Constructors, Destructor and Operators
        public:
            /**
             *  Default constructor
             */
            inline coroutine() :
                job_p_(0),
                fiber_(
                    pac::fiber_creation_mode::NEW,
                    [&](pac::fiber& fiber) {

                        main_loop();

                    }
                )
            {


            
            }
            /**
             *  Destructor
             */
            ~coroutine() {



            }
#pragma endregion



#pragma region Methods
        private:
            void main_loop();


        public:
            /**
             *  Binds the job to run in the next time "switch_to_this" called
             */
            inline void bind_job(dop::job& j) {

                job_p_ = &j;

            }

            /**
             *  Switches from the current thread's fiber to this fiber
             */
            inline void switch_to_this() {

                fiber_.switch_to_this();

            }
#pragma endregion

        };



        /**
         *  Coroutine pool is an object managing and storing coroutines
         */
        class NCPP_DEFAULT_ALIGNAS coroutine_pool
        {

#pragma region Typedefs
        public:
            using coroutine_allocator_type = tgh_allocator_t<coroutine>;
            using coroutine_vector_type = std::vector<coroutine, coroutine_allocator_type>;
            using coroutine_p_allocator_type = tgh_allocator_t<coroutine*>;
            using coroutine_p_stack_type = containers::fixed_vector_stack_t<coroutine*, coroutine_p_allocator_type>;
#pragma endregion
            


#pragma region Properties
        private:
            coroutine_allocator_type coroutine_allocator_;
            coroutine_vector_type coroutine_vector_;
            coroutine_p_allocator_type coroutine_p_allocator_;
            coroutine_p_stack_type coroutine_p_stack_;
#pragma endregion



#pragma region Constructors, Destructor and Operators
        public:
            /**
             *  Default constructor
             */
            coroutine_pool();

            /**
             *  Destructor
             */
            ~coroutine_pool() {



            }

            inline coroutine_pool(const coroutine_pool&) = delete;
            inline coroutine_pool& operator = (const coroutine_pool&) = delete;
            inline coroutine_pool(coroutine_pool&&) = delete;
            inline coroutine_pool& operator = (coroutine_pool&&) = delete;
#pragma endregion



#pragma region Methods
        public:
            /**
             *  Pops a coroutine pointer from the coroutine pointer stack
             */
            inline coroutine* pop() {

                coroutine* r = coroutine_p_stack_.back();

                coroutine_p_stack_.pop();

                return r;
            }
            /**
             *  Push a coroutine pointer back to the coroutine pointer stack
             */
            inline void push(coroutine* coroutine_p) {

                coroutine_p_stack_.push(coroutine_p);
            }
#pragma endregion

        };

	}

}