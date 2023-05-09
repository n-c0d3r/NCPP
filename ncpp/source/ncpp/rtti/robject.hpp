#pragma once

/**
 *  @file ncpp/rtti/robject.hpp
 *  @brief Implements reflected object.
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
#include <ncpp/iostream.hpp>

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/rtti/rclass.hpp>

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



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        /**
         *  Indicates a class need to be reflected.
         *  Must be added first in class body.
         */
#define NCPP_RCLASS(ClassName) \
        private: \
            using current_rclass = ClassName;\
            ncpp::rtti::robject_constructor_begin_scope __##ClassName##_constructor_begin_scope__; \
        public: \
            virtual ncpp::rtti::rclass_t<ncpp::rtti::robject_i> get_rclass() const { \
                return ncpp::rtti::rclass_t<ClassName>(); \
            } \
            static inline ncpp::rtti::rclass_t<ClassName> get_static_rclass() { \
                return ncpp::rtti::rclass_t<ClassName>(); \
            } \
            inline ClassName(const ClassName& other) : ClassName() \
            {\
                *this = other;\
            }\
            inline ClassName& operator = (const ClassName& other) {\
                copy(other);\
                return *this;\
            }\
            inline ClassName& instantiate() const {\
                ClassName& result = (ClassName&)get_rclass().create_instance();\
                result = *this;\
                return result;\
            }\
            inline ncpp::utilities::native_shared_ptr_t<ClassName> shared_instantiate() const {\
                ncpp::utilities::native_shared_ptr_t<ClassName> result = ncpp::utilities::native_shared_ptr_cast_t<ClassName>(get_rclass().create_shared_instance());\
                *result = *this;\
                return result;\
            }\
            inline ncpp::utilities::native_unique_ptr_t<ClassName> unique_instantiate() const {\
                ncpp::utilities::native_unique_ptr_t<ClassName> result = ncpp::utilities::native_unique_ptr_cast_t<ClassName>(get_rclass().create_unique_instance());\
                *result = *this;\
                return result;\
            }\
        private:  

        /**
         *  Setups the constructing scope of a reflected class.
         *  Must be added first in constructor body.
         */
#define NCPP_RCSCOPE(ClassName) \
        ncpp::rtti::robject_constructor_end_scope __robject_constructor_end_scope__(*this, *(__##ClassName##_constructor_begin_scope__.prev_robject_ref));

        /**
         *  Declares a reflected member variable.
         */
#define NCPP_RCVARIABLE(MemberType, MemberName, ...) \
        MemberType MemberName;\
        char MemberName##_name_cstr[sizeof(#MemberName)] = #MemberName;\
        using MemberName##_args_type = typename ncpp::rtti::robject_member_args_t<__VA_ARGS__>;\
        MemberName##_args_type MemberName##_args = {__VA_ARGS__}; \
        using MemberName##_reflecter_type = ncpp::rtti::robject_variable_reflecter_t<\
            current_rclass, \
            MemberType, \
            decltype(&current_rclass::MemberName##_name_cstr),\
            &current_rclass::MemberName##_name_cstr,\
            decltype(&current_rclass::MemberName##_args),\
            &current_rclass::MemberName##_args,\
            decltype(&current_rclass::MemberName),\
            &current_rclass::MemberName\
        >; \
        friend class MemberName##_reflecter_type; \
        MemberName##_reflecter_type MemberName##_reflecter;

        /**
         *  Declares a reflected member function.
         */
#define NCPP_RCFUNCTION(MemberFunctionType, MemberName,...) \
        using MemberName##_type = MemberFunctionType; \
        MemberName##_type MemberName; \
        char MemberName##_name_cstr[sizeof(#MemberName)] = #MemberName;\
        typename ncpp::rtti::robject_member_args_t<__VA_ARGS__> MemberName##_args = {__VA_ARGS__}; \
        typename std::function<MemberFunctionType> MemberName##_functor; \
        using MemberName##_reflecter_type = ncpp::rtti::robject_function_reflecter_t<\
            current_rclass, \
            MemberFunctionType, \
            decltype(&current_rclass::MemberName##_name_cstr),\
            &current_rclass::MemberName##_name_cstr,\
            decltype(&current_rclass::MemberName##_args),\
            &current_rclass::MemberName##_args,\
            decltype(&current_rclass::MemberName##_functor),\
            &current_rclass::MemberName##_functor,\
            decltype(&current_rclass::MemberName), \
            &current_rclass::MemberName \
        >; \
        friend class MemberName##_reflecter_type; \
        MemberName##_reflecter_type MemberName##_reflecter;



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        /**
         *  Stores member's arguments.
         */
        template<sz... args__>
        using robject_member_args_t = typename std::array<sz, sizeof... (args__)>;



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        /**
         *  Gets the current constructing object.
         */
        robject_i& current_constructing_object();



        class robject_constructor_begin_scope;
        class robject_constructor_end_scope;



        /**
         *  .
         */
        class robject_constructor_begin_scope {

            friend class robject_i;

        public:
            utilities::lref_t<robject_i> prev_robject_ref;

        public:
            robject_constructor_begin_scope();
            ~robject_constructor_begin_scope();

        };

        /**
         *  .
         */
        class robject_constructor_end_scope {

            friend class robject_i;

        public:
            utilities::lref_t<robject_i> prev_robject_ref;

        public:
            robject_constructor_end_scope(robject_i& robject, robject_i& prev_robject);
            inline robject_constructor_end_scope() :
                robject_constructor_end_scope(*utilities::lref_t<robject_i>(), *utilities::lref_t<robject_i>())
            {}
            ~robject_constructor_end_scope();

        };



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        /**
         *  Stores member's arguments pointer, robject pointer and member pointer.
         */
        struct robject_member_handle {

            struct args_array_type {

                sz* head_arg_p = 0;
                sz arg_count = 0;

                inline const sz& head() const {

                    return *head_arg_p;
                }
                inline const sz& tail() const {

                    return *(head_arg_p + arg_count - 1);
                }
                inline const sz* begin() const {

                    return head_arg_p;
                }
                inline const sz* end() const {

                    return head_arg_p + arg_count;
                }

            };



            using logger_func_ptr_type = void(*)(
                std::ostream& os, 
                const ostream_input_t<
                    robject_member_handle
                >& input
            );
            using copy_func_ptr_type = void(*)(const robject_i& from, robject_i& to);



            args_array_type args_array;
            b8 is_function = 0;
            logger_func_ptr_type logger_func_ptr = 0;
            void* member_ptr_p = 0;
            copy_func_ptr_type copy_func_ptr = 0;



            inline robject_member_handle() {


            }
            inline robject_member_handle(const robject_member_handle& other) :
                args_array(other.args_array),
                is_function(other.is_function),
                logger_func_ptr(other.logger_func_ptr),
                member_ptr_p(other.member_ptr_p),
                copy_func_ptr(other.copy_func_ptr)
            {



            }
            inline robject_member_handle& operator = (const robject_member_handle& other) {

                args_array = other.args_array;
                is_function = other.is_function;
                logger_func_ptr = other.logger_func_ptr;
                member_ptr_p = other.member_ptr_p;
                copy_func_ptr = other.copy_func_ptr;

                return *this;
            }



            friend inline std::ostream& operator << (
                std::ostream& os,
                const ostream_input_t<
                    robject_member_handle
                >& input
            )
            {

                input.first.logger_func_ptr(os, input);

                return os;
            }

            friend inline std::ostream& operator << (std::ostream& os, const robject_member_handle& member_handle)
            {

                os << ostream_input_t<robject_member_handle> { member_handle, 0 };

                return os;
            }



            /**
             *  The type that is recorrected by the rules:
             *      1. if type__ is function type, return std::function<type__>.
             *      2. if type__ is not function type, return type__.
             */
            template<typename type__>
            using recorrected_type_t = typename utilities::nth_template_arg_t<
                utilities::is_function_t<type__>::value,
                type__,
                typename std::function<type__>
            >::type;



            /**
             *  Casts to recorrected type__.
             */
            template<typename type__>
            inline recorrected_type_t<type__>& to_t() {

                return *reinterpret_cast<recorrected_type_t<type__>*>(member_ptr_p);
            }

            /**
             *  Casts to recorrected type__.
             */
            template<typename type__>
            inline recorrected_type_t<const type__>& to_t() const {

                return *reinterpret_cast<recorrected_type_t<const type__>*>(member_ptr_p);
            }



            /**
             *  Sets the value of member data from other data.
             */
            template<typename type__>
            inline robject_member_handle& operator = (
                typename utilities::nth_template_arg_t<
                    std::is_same_v<type__, robject_member_handle>,
                    type__,
                    void
                >::type&& 
                other
            ) {

                static_assert(!utilities::is_function_t<type__>::value && "type__ must not be function type");
                assert(!is_function && "this is not function");

                to_t<std::remove_reference<type__>::type>() = std::forward<type__>(other);

                return *this;
            }



            /**
             *  Checks if the value of member data equal to other data.
             */
            template<typename type__>
            inline b8 operator == (type__&& other) {

                static_assert(!utilities::is_function_t<type__>::value && "type__ must not be function type");
                assert(!is_function && "this is not function");

                return to_t<std::remove_reference<type__>::type>() == std::forward<type__>(other);
            }

            /**
             *  Checks if the value of member data not equal to other data.
             */
            template<typename type__>
            inline b8 operator != (type__&& other) {

                static_assert(!utilities::is_function_t<type__>::value && "type__ must not be function type");
                assert(!is_function && "this is not function");

                return to_t<std::remove_reference<type__>::type>() != std::forward<type__>(other);
            }

            /**
             *  Checks if the value of member data greater than other data.
             */
            template<typename type__>
            inline b8 operator > (type__&& other) {

                static_assert(!utilities::is_function_t<type__>::value && "type__ must not be function type");
                assert(!is_function && "this is not function");

                return to_t<std::remove_reference<type__>::type>() > std::forward<type__>(other);
            }

            /**
             *  Checks if the value of member data less than other data.
             */
            template<typename type__>
            inline b8 operator < (type__ && other) {

                static_assert(!utilities::is_function_t<type__>::value && "type__ must not be function type");
                assert(!is_function && "this is not function");

                return to_t<std::remove_reference<type__>::type>() < std::forward<type__>(other);
            }

            /**
             *  Checks if the value of member data greater than or equal to other data.
             */
            template<typename type__>
            inline b8 operator >= (type__&& other) {

                static_assert(!utilities::is_function_t<type__>::value && "type__ must not be function type");
                assert(!is_function && "this is not function");

                return to_t<std::remove_reference<type__>::type>() >= std::forward<type__>(other);
            }

            /**
             *  Checks if the value of member data less than or equal to other data.
             */
            template<typename type__>
            inline b8 operator <= (type__&& other) {

                static_assert(!utilities::is_function_t<type__>::value && "type__ must not be function type");
                assert(!is_function && "this is not function");

                return to_t<std::remove_reference<type__>::type>() <= std::forward<type__>(other);
            }

        };



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        template<
            class object_type__,
            typename variable_type__,
            typename name_member_ptr_type,
            name_member_ptr_type name_member_ptr,
            typename args_member_ptr_type,
            args_member_ptr_type args_member_ptr,
            typename member_ptr_type,
            member_ptr_type member_ptr
        >
        class robject_variable_reflecter_t
        {

        public:
            robject_variable_reflecter_t();
            ~robject_variable_reflecter_t();

        };



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        template<
            class object_type__,
            typename function_type__,
            typename name_member_ptr_type,
            name_member_ptr_type name_member_ptr,
            typename args_member_ptr_type,
            args_member_ptr_type args_member_ptr,
            typename functor_member_ptr_type,
            functor_member_ptr_type functor_member_ptr,
            typename member_ptr_type,
            member_ptr_type member_ptr
        >
        class robject_function_reflecter_t
        {

        public:
            typedef void* executer_type;



        public:
            robject_function_reflecter_t();
            ~robject_function_reflecter_t();

            template<b8 is_void_return__>
            struct executer_get_t;

        };



        template<
            class object_type__,
            typename function_type__,
            b8 is_void_return__,
            typename name_member_ptr_type,
            name_member_ptr_type name_member_ptr,
            typename args_member_ptr_type,
            args_member_ptr_type args_member_ptr,
            typename functor_member_ptr_type,
            functor_member_ptr_type functor_member_ptr,
            typename member_ptr_type,
            member_ptr_type member_ptr
        >
        struct robject_function_reflecter_executer_get_t {

        };



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





        /**
         *  Reflected object interface.
         */
        class robject_i {

            NCPP_RCLASS(robject_i);

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        public:
            using name_to_member_handle_map_type = typename containers::native_unordered_map_t<containers::native_string, robject_member_handle>;

            friend class robject_constructor_scope;

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////

        private:
            name_to_member_handle_map_type name_to_member_handle_map_;

        public:
            inline name_to_member_handle_map_type::iterator begin() {

                return name_to_member_handle_map_.begin();
            }
            inline name_to_member_handle_map_type::const_iterator begin() const {

                return name_to_member_handle_map_.cbegin();
            }
            inline name_to_member_handle_map_type::const_iterator cbegin() const {

                return name_to_member_handle_map_.cbegin();
            }

            inline name_to_member_handle_map_type::iterator end() {

                return name_to_member_handle_map_.end();
            }
            inline name_to_member_handle_map_type::const_iterator end() const {

                return name_to_member_handle_map_.cend();
            }
            inline name_to_member_handle_map_type::const_iterator cend() const {

                return name_to_member_handle_map_.cend();
            }

			////////////////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////

#pragma region Constructors, Destructor and Operators
        public:
            robject_i();
            virtual ~robject_i();

            virtual void copy(const robject_i& other);



        public:
            /**
             *  Gets member handle by name.
             */
            inline robject_member_handle& operator [] (const containers::native_string& member_name) {

                if (name_to_member_handle_map_.find(member_name) != name_to_member_handle_map_.end())
                    return name_to_member_handle_map_.find(member_name)->second;

                return *utilities::lref_t<robject_member_handle>();
            }
            /**
             *  Gets member handle by name.
             */
            inline const robject_member_handle& operator [] (const containers::native_string& member_name) const {

                if (name_to_member_handle_map_.find(member_name) != name_to_member_handle_map_.end())
                    return name_to_member_handle_map_.find(member_name)->second;

                return *utilities::lref_t<const robject_member_handle>();
            }
#pragma endregion

			////////////////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////

#pragma region Methods
        protected:
            void copy_variable_members(const robject_i& other);
            void copy_variable_member(const robject_i& other, const containers::native_string& member_name);



		public:
            /**
             *  Checks if the robject has member named <member_name>
             */
            inline b8 is_has_member(const containers::native_string& member_name) const {

                if (name_to_member_handle_map_.find(member_name) != name_to_member_handle_map_.end())
                    return true;

                return false;
            }

            /**
             *  Adds a member handle into name_to_member_handle_map_.
             */
            inline void add_member_handle(const containers::native_string& member_name, const robject_member_handle& handle) {

                assert(!is_has_member(member_name) && "member already existed");

                name_to_member_handle_map_[member_name] = handle;

            }

            /**
             *  Gets reflected variable by name.
             */
            template<typename variable_type__>
            inline variable_type__& var_t(const containers::native_string& var_name) {

                return at(var_name).to_t<variable_type__>();
            }

            /**
             *  Gets reflected function by name.
             */
            template<typename function_type__>
            inline const std::function<function_type__>& func_t(const containers::native_string& func_name) const {

                return at(var_name).to_t<function_type__>();
            }

            /**
             *  Gets reflected variable by name.
             */
            template<typename variable_type__>
            inline const variable_type__& var_t(const containers::native_string& var_name) const {

                return at(var_name).to_t<variable_type__>();
            }

            /**
             *  Gets member handle by name.
             */
            inline robject_member_handle& at(const containers::native_string& member_name) {

                if (name_to_member_handle_map_.find(member_name) != name_to_member_handle_map_.end())
                    return name_to_member_handle_map_.find(member_name)->second;

                return *utilities::lref_t<robject_member_handle>();
            }
            /**
             *  Gets member handle by name.
             */
            inline const robject_member_handle& at(const containers::native_string& member_name) const {

                if (name_to_member_handle_map_.find(member_name) != name_to_member_handle_map_.end())
                    return name_to_member_handle_map_.find(member_name)->second;

                return *utilities::lref_t<const robject_member_handle>();
            }
#pragma endregion

        };




        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        template<
            class object_type__,
            typename variable_type__,
            typename name_member_ptr_type,
            name_member_ptr_type name_member_ptr,
            typename args_member_ptr_type,
            args_member_ptr_type args_member_ptr,
            typename member_ptr_type,
            member_ptr_type member_ptr
        >
        robject_variable_reflecter_t<
            object_type__,
            variable_type__,
            name_member_ptr_type,
            name_member_ptr,
            args_member_ptr_type,
            args_member_ptr,
            member_ptr_type,
            member_ptr
        >::robject_variable_reflecter_t() {

            object_type__& robj = (object_type__&)current_constructing_object();

            robject_member_handle rvar_handle;
            rvar_handle.args_array = {
                (robj.*args_member_ptr).data(),
                (robj.*args_member_ptr).size()
            };
            rvar_handle.is_function = 0;
            rvar_handle.member_ptr_p = &(robj.*member_ptr);

            rvar_handle.logger_func_ptr = [](
                std::ostream& os, 
                const ostream_input_t<
                    robject_member_handle
                >& input
            ) {

                safe_ostream_with_tab_t<std::ostream, variable_type__>(
                    os, 
                    { 
                        *reinterpret_cast<variable_type__*>(input.first.member_ptr_p),
                        input.second + 1 
                    }
                );
                //safe_ostream_t(os, *reinterpret_cast<variable_type__*>(member_handle.member_ptr_p));

            };

            rvar_handle.copy_func_ptr = [](const robject_i& from, robject_i& to) {

                (((object_type__&)to).*member_ptr) = (((object_type__&)from).*member_ptr);

            };

            robj.add_member_handle(robj.*name_member_ptr, rvar_handle);

        }

        template<
            class object_type__,
            typename variable_type__,
            typename name_member_ptr_type,
            name_member_ptr_type name_member_ptr,
            typename args_member_ptr_type,
            args_member_ptr_type args_member_ptr,
            typename member_ptr_type,
            member_ptr_type member_ptr
        >
        robject_variable_reflecter_t<
            object_type__,
            variable_type__,
            name_member_ptr_type,
            name_member_ptr,
            args_member_ptr_type,
            args_member_ptr,
            member_ptr_type,
            member_ptr
        >::~robject_variable_reflecter_t() {



        }



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        template<
            class object_type__,
            typename function_type__,
            typename name_member_ptr_type,
            name_member_ptr_type name_member_ptr,
            typename args_member_ptr_type,
            args_member_ptr_type args_member_ptr,
            typename functor_member_ptr_type,
            functor_member_ptr_type functor_member_ptr,
            typename member_ptr_type,
            member_ptr_type member_ptr
        >
        robject_function_reflecter_t<
            object_type__,
            function_type__,
            name_member_ptr_type,
            name_member_ptr,
            args_member_ptr_type,
            args_member_ptr,
            functor_member_ptr_type,
            functor_member_ptr,
            member_ptr_type,
            member_ptr
        >::robject_function_reflecter_t(){

            object_type__& robj = (object_type__&)current_constructing_object();

            using function_traits = typename utilities::function_traits_t<function_type__>;

            using executer_getter_type = typename robject_function_reflecter_executer_get_t<
                object_type__,
                function_type__,
                std::is_same_v<function_traits::result_type, void>,
                name_member_ptr_type,
                name_member_ptr,
                args_member_ptr_type,
                args_member_ptr,
                functor_member_ptr_type,
                functor_member_ptr,
                member_ptr_type,
                member_ptr
            >;
                        
            executer_type rfunc_executer = executer_getter_type::get(robj);

            robject_member_handle rfunc_handle;
            rfunc_handle.args_array = {
                (robj.*args_member_ptr).data(),
                (robj.*args_member_ptr).size()
            };
            rfunc_handle.is_function = 1;
            rfunc_handle.member_ptr_p = reinterpret_cast<void*>(rfunc_executer);

            rfunc_handle.logger_func_ptr = [](
                std::ostream& os,
                const ostream_input_t<
                    robject_member_handle
                >& input
            ) {

                os << typeid(function_type__).name() << " { ";

                safe_ostream_t(os, input.first.member_ptr_p);
                
                os << " }";

            };

            robj.add_member_handle(robj.*name_member_ptr, rfunc_handle);

        }

        template<
            class object_type__,
            typename function_type__,
            typename name_member_ptr_type,
            name_member_ptr_type name_member_ptr,
            typename args_member_ptr_type,
            args_member_ptr_type args_member_ptr,
            typename functor_member_ptr_type,
            functor_member_ptr_type functor_member_ptr,
            typename member_ptr_type,
            member_ptr_type member_ptr
        >
        robject_function_reflecter_t<
            object_type__,
            function_type__,
            name_member_ptr_type,
            name_member_ptr,
            args_member_ptr_type,
            args_member_ptr,
            functor_member_ptr_type,
            functor_member_ptr,
            member_ptr_type,
            member_ptr
        >::~robject_function_reflecter_t() {



        }

        template<
            class object_type__,
            typename function_type__,
            typename name_member_ptr_type,
            name_member_ptr_type name_member_ptr,
            typename args_member_ptr_type,
            args_member_ptr_type args_member_ptr,
            typename functor_member_ptr_type,
            functor_member_ptr_type functor_member_ptr,
            typename member_ptr_type,
            member_ptr_type member_ptr
        >
        struct robject_function_reflecter_executer_get_t <
            object_type__,
            function_type__,
            true,
            name_member_ptr_type,
            name_member_ptr,
            args_member_ptr_type,
            args_member_ptr,
            functor_member_ptr_type,
            functor_member_ptr,
            member_ptr_type,
            member_ptr
        >
        {

            using executer_type = typename robject_function_reflecter_t<
                object_type__,
                function_type__,
                name_member_ptr_type,
                name_member_ptr,
                args_member_ptr_type,
                args_member_ptr,
                functor_member_ptr_type,
                functor_member_ptr,
                member_ptr_type,
                member_ptr
            >::executer_type;

            using function_traits = typename utilities::function_traits_t<function_type__>;

            static inline executer_type get(object_type__& robj) {

                (robj.*functor_member_ptr) = [&robj](auto&&... args) -> function_traits::result_type {

                    (robj.*member_ptr)(std::forward<decltype(args)>(args)...);

                };

                return &(robj.*functor_member_ptr);
            }

        };

        template<
            class object_type__,
            typename function_type__,
            typename name_member_ptr_type,
            name_member_ptr_type name_member_ptr,
            typename args_member_ptr_type,
            args_member_ptr_type args_member_ptr,
            typename functor_member_ptr_type,
            functor_member_ptr_type functor_member_ptr,
            typename member_ptr_type,
            member_ptr_type member_ptr
        >
        struct robject_function_reflecter_executer_get_t <
            object_type__,
            function_type__,
            false,
            name_member_ptr_type,
            name_member_ptr,
            args_member_ptr_type,
            args_member_ptr,
            functor_member_ptr_type,
            functor_member_ptr,
            member_ptr_type,
            member_ptr
        >
        {

            using executer_type = typename robject_function_reflecter_t<
                object_type__,
                function_type__,
                name_member_ptr_type,
                name_member_ptr,
                args_member_ptr_type,
                args_member_ptr,
                functor_member_ptr_type,
                functor_member_ptr,
                member_ptr_type,
                member_ptr
            >::executer_type;

            using function_traits = typename utilities::function_traits_t<function_type__>;

            static inline executer_type get(object_type__& robj) {

                (robj.*functor_member_ptr) = [&robj](auto&&... args) -> function_traits::result_type {

                    return (robj.*member_ptr)(std::forward<decltype(args)>(args)...);

                };

                return &(robj.*functor_member_ptr);
            }

        };



        inline std::ostream& operator << (
            std::ostream& os,
            const ostream_input_t<
                robject_i
            >& input
        )
        {

            os << "{" << std::endl;

            b8 is_first_member = true;

            for (const auto& member_handle : input.first) {

                if (!is_first_member) {

                    os << ",";
                    os << std::endl;

                }

                is_first_member = false;

                for (u32 j = 0; j < (input.second + 1) * NCPP_TAB_SIZE; ++j) {

                    os << " ";

                }

                os << '"' << member_handle.first << '"' << ": ";
                safe_ostream_with_tab_t<std::ostream, decltype(member_handle.second)>(os, { member_handle.second, input.second });

            }

            os << std::endl;

            for (u32 j = 0; j < (input.second) * NCPP_TAB_SIZE; ++j) {

                os << " ";

            }
            os << "}";

            return os;
        }

        inline std::ostream& operator << (std::ostream& os, const robject_i& obj)
        {

            os << ostream_input_t<robject_i> { obj, 0 };

            return os;
        }

    }

}