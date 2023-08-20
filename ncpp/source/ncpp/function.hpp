#pragma once

/**
 *  @file ncpp/utilities/function.hpp
 *  @brief Implements function.
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

#include <ncpp/mem.hpp>

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/utilities/.hpp>

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



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    namespace lambda_helper {

        template<typename lambda_passed_type__, typename allocator_type__>
        inline std::remove_const_t<std::remove_reference_t<lambda_passed_type__>>* clone_lambda_t(lambda_passed_type__&& other, const allocator_type__& allocator) {
        
            using lambda_type = std::remove_const_t<std::remove_reference_t<lambda_passed_type__>>;

            lambda_type* result = new(
                reinterpret_cast<lambda_type*>(
                    allocator.allocate(sizeof(lambda_type))
                )
            ) lambda_type(std::forward<lambda_passed_type__>(other));

            return result;
        }



        template<typename lambda_type__, b8 is_return_void__, typename return_type__, typename... arg_types__>
        struct run_t;

        template<typename lambda_type__, typename return_type__, typename... arg_types__>
        struct run_t<lambda_type__, true, return_type__, arg_types__...> {

            static return_type__ invoke(void* lambda_p, arg_types__... args) {

                (*reinterpret_cast<lambda_type__*>(lambda_p))(std::forward<arg_types__>(args)...);

            }

        };

        template<typename lambda_type__, typename return_type__, typename... arg_types__>
        struct run_t<lambda_type__, false, return_type__, arg_types__...> {

            static return_type__ invoke(void* lambda_p, arg_types__... args) {

                return (*reinterpret_cast<lambda_type__*>(lambda_p))(std::forward<arg_types__>(args)...);
            }

        };



        template<typename lambda_type__, typename allocator_type__>
        struct clone_t {

            static void* invoke(void* lambda_p, allocator_type__& allocator) {

                return reinterpret_cast<void*>(
                    clone_lambda_t<lambda_type__&, allocator_type__>(
                        *reinterpret_cast<lambda_type__*>(lambda_p),
                        allocator
                    )
                );
            }

        };



        template<typename lambda_type__, typename allocator_type__>
        struct release_t {

            static void invoke(void* lambda_p, allocator_type__& allocator) {

                reinterpret_cast<lambda_type__*>(lambda_p)->~lambda_type__();

                allocator.deallocate(reinterpret_cast<u8*>(lambda_p));

            }

        };



        template<typename lambda_type__, typename allocator_type__, b8 is_return_void__, typename return_type__, typename... arg_types__>
        inline sz table_t[];

        template<typename lambda_type__, typename allocator_type__, typename return_type__, typename... arg_types__>
        inline sz table_t<lambda_type__, allocator_type__, true, return_type__, arg_types__...>[] = {

            //Run
            reinterpret_cast<sz>(
                &run_t<
                    lambda_type__, 
                    std::is_same_v<void, return_type__>, 
                    return_type__, 
                    arg_types__...
                >::invoke
            ),

            //Release
            reinterpret_cast<sz>(
                &release_t<
                    lambda_type__,
                    allocator_type__
                >::invoke
            ),

            //Clone
            reinterpret_cast<sz>(
                &clone_t<
                    lambda_type__,
                    allocator_type__
                >::invoke
            )

        };

        template<typename lambda_type__, typename allocator_type__, typename return_type__, typename... arg_types__>
        inline sz* get_table_t() {

            return table_t<lambda_type__, allocator_type__, std::is_same_v<return_type__, void>, return_type__, arg_types__...>;
        };

        template<typename return_type__, typename... arg_types__>
        using run_function_ptr_type_t = return_type__(*)(void* lambda, arg_types__...);

        template<typename return_type__, typename... arg_types__>
        inline run_function_ptr_type_t<return_type__, arg_types__...> get_run_function_t(sz* table) {

            return reinterpret_cast<run_function_ptr_type_t<return_type__, arg_types__...>>(table[0]);
        };

        using release_function_ptr_type = void(*)(void* lambda);

        inline release_function_ptr_type get_release_function(sz* table) {

            return reinterpret_cast<release_function_ptr_type>(table[1]);
        };

        using clone_function_ptr_type = void*(*)(void* lambda);

        inline clone_function_ptr_type get_clone_function(sz* table) {

            return reinterpret_cast<clone_function_ptr_type>(table[2]);
        };

    }



    template<typename raw_type__, class allocator_type__ = NCPP_DEFAULT_ALLOCATOR_TEMPLATE<u8>>
    class function_base_t;

    template<class allocator_type__, typename return_type__, typename... arg_types__>
    class function_base_t<return_type__(arg_types__...), allocator_type__> {

    public:
        using raw_type = return_type__(arg_types__...);
        using traits = utilities::function_traits_t<raw_type>;
        using allocator_type = allocator_type__;



    public:
        void* data_p_ = 0;

        sz* table_p_ = 0;

        allocator_type__ allocator_;

    };



    template<b8 is_return_void, typename raw_type__, class allocator_type__ = NCPP_DEFAULT_ALLOCATOR_TEMPLATE<u8>>
    class function_operator_applied_t;

    template<class allocator_type__, typename return_type__, typename... arg_types__>
    class function_operator_applied_t<true, return_type__(arg_types__...), allocator_type__> :
        protected function_base_t<
            return_type__(arg_types__...),
            allocator_type__
        >
    {

    protected:
        using base = function_base_t<
            return_type__(arg_types__...),
            allocator_type__
        >;



    public:
        inline return_type__ operator() (arg_types__... args) {

            if (reinterpret_cast<sz*>(reinterpret_cast<base*>(this)->table_p_) != 0) {

                lambda_helper::get_run_function_t<return_type__, arg_types__...>(
                    reinterpret_cast<sz*>(reinterpret_cast<base*>(this)->table_p_)
                )(
                    reinterpret_cast<base*>(this)->data_p_,
                    std::forward<arg_types__>(args)...
                );
                return;

            }

            reinterpret_cast<typename base::raw_type*>(reinterpret_cast<base*>(this)->data_p_)(std::forward<arg_types__>(args)...);
        }

    };

    template<class allocator_type__, typename return_type__, typename... arg_types__>
    class function_operator_applied_t<false, return_type__(arg_types__...), allocator_type__> :
        protected function_base_t<
            return_type__(arg_types__...), 
            allocator_type__
        >
    {

    protected:
        using base = function_base_t<
            return_type__(arg_types__...),
            allocator_type__
        >;



    public:
        inline return_type__ operator() (arg_types__... args) {

            reinterpret_cast<typename base::raw_type*>(reinterpret_cast<base*>(this)->data_p_)(std::forward<arg_types__>(args)...);
        }

    };



    template<typename raw_type__, class allocator_type__ = NCPP_DEFAULT_ALLOCATOR_TEMPLATE<u8>>
    class function_t;

    template<class allocator_type__, typename return_type__, typename... arg_types__>
    class function_t<return_type__(arg_types__...), allocator_type__> :
        public function_operator_applied_t<
            std::is_same_v<return_type__, void>, 
            return_type__(arg_types__...), 
            allocator_type__
        >
    {

        using base = typename function_operator_applied_t<
            std::is_same_v<return_type__, void>,
            return_type__(arg_types__...),
            allocator_type__
        >::base;

        using operators = function_operator_applied_t<
            std::is_same_v<return_type__, void>,
            return_type__(arg_types__...),
            allocator_type__
        >;



    public:
        inline function_t() {



        }

        inline function_t(typename base::raw_type* raw_function_p) {

            *reinterpret_cast<typename base::raw_type**>(&(reinterpret_cast<base*>(this)->data_p_)) = raw_function_p;

        }
        template<
            typename lambda_passed_type__, 
            std::enable_if_t<
                std::is_convertible_v<lambda_passed_type__, typename base::raw_type*>
                && !std::is_same_v<function_t, std::remove_const_t<std::remove_reference_t<lambda_passed_type__>>>,
                int
            > = 0
        >
        inline function_t(lambda_passed_type__&& lambda) {

            *reinterpret_cast<typename base::raw_type**>(&(reinterpret_cast<base*>(this)->data_p_)) = std::forward<lambda_passed_type__>(lambda);

        }

        template<
            typename lambda_passed_type__,
            std::enable_if_t<
                !std::is_convertible_v<lambda_passed_type__, typename base::raw_type*>
                && !std::is_same_v<function_t, std::remove_const_t<std::remove_reference_t<lambda_passed_type__>>>,
                int
            > = 0
        >
        inline function_t(lambda_passed_type__&& lambda, const allocator_type__& allocator = allocator_type__())
        {

            using lambda_type = std::remove_const_t<std::remove_reference_t<lambda_passed_type__>>;

            reinterpret_cast<base*>(this)->allocator_ = allocator;

            reinterpret_cast<base*>(this)->data_p_ = lambda_helper::clone_lambda_t(
                std::forward<lambda_passed_type__>(lambda),
                reinterpret_cast<base*>(this)->allocator_
            );

            reinterpret_cast<base*>(this)->table_p_ = lambda_helper::get_table_t<lambda_type, allocator_type__, return_type__, arg_types__...>();

        }

        ~function_t() {

            clear_lambda_data();

        }

        inline function_t(const function_t& other) 
        {

            clear_lambda_data();

            if (reinterpret_cast<const base*>(&other)->table_p_ != 0) {

                reinterpret_cast<base*>(this)->allocator_ = reinterpret_cast<const base*>(&other)->allocator_;

                reinterpret_cast<base*>(this)->data_p_ = (
                    lambda_helper::get_clone_function(
                        reinterpret_cast<const base*>(&other)->table_p_
                    )(
                        reinterpret_cast<const base*>(&other)->data_p_
                    )
                );

                reinterpret_cast<base*>(this)->table_p_ = reinterpret_cast<const base*>(&other)->table_p_;

            }
            else {

                reinterpret_cast<base*>(this)->data_p_ = reinterpret_cast<const base*>(&other)->data_p_;
                reinterpret_cast<base*>(this)->table_p_ = reinterpret_cast<const base*>(&other)->table_p_;

            }

        }

        inline function_t& operator = (const function_t& other) {

            clear_lambda_data();

            if (reinterpret_cast<const base*>(&other)->table_p_ != 0) {

                reinterpret_cast<base*>(this)->allocator_ = reinterpret_cast<const base*>(&other)->allocator_;

                reinterpret_cast<base*>(this)->data_p_ = (
                    lambda_helper::get_clone_function(
                        reinterpret_cast<const base*>(&other)->table_p_
                    )(
                        reinterpret_cast<const base*>(&other)->data_p_
                        )
                    );

                reinterpret_cast<base*>(this)->table_p_ = reinterpret_cast<const base*>(&other)->table_p_;

            }
            else {

                reinterpret_cast<base*>(this)->data_p_ = reinterpret_cast<const base*>(&other)->data_p_;
                reinterpret_cast<base*>(this)->table_p_ = reinterpret_cast<const base*>(&other)->table_p_;

            }

            return *this;
        }

        inline function_t(function_t&& other)
        {

            clear_lambda_data();

            reinterpret_cast<base*>(this)->allocator_ = std::move(reinterpret_cast<base*>(&other)->allocator_);
            reinterpret_cast<base*>(this)->data_p_ = reinterpret_cast<base*>(&other)->data_p_;
            reinterpret_cast<base*>(this)->table_p_ = reinterpret_cast<base*>(&other)->table_p_;

            reinterpret_cast<base*>(&other)->data_p_ = 0;
            reinterpret_cast<base*>(&other)->table_p_ = 0;

        }

        inline function_t& operator = (function_t&& other)
        {

            clear_lambda_data();

            reinterpret_cast<base*>(this)->allocator_ = std::move(reinterpret_cast<base*>(&other)->allocator_);
            reinterpret_cast<base*>(this)->data_p_ = reinterpret_cast<base*>(&other)->data_p_;
            reinterpret_cast<base*>(this)->table_p_ = reinterpret_cast<base*>(&other)->table_p_;

            reinterpret_cast<base*>(&other)->data_p_ = 0;
            reinterpret_cast<base*>(&other)->table_p_ = 0;

            return *this;
        }



    private:
        inline void clear_lambda_data() {

            if (reinterpret_cast<base*>(this)->table_p_ != 0) {

                lambda_helper::get_release_function(
                    reinterpret_cast<base*>(this)->table_p_
                )(
                    reinterpret_cast<base*>(this)->data_p_
                );

            }

            reinterpret_cast<base*>(this)->data_p_ = 0;

        }

    };



    template<typename raw_function_type__>
    using native_function_t = function_t<raw_function_type__, native_allocator_t<u8>>;


}