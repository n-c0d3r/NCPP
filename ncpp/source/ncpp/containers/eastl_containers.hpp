#pragma once

/** @file ncpp/containers/eastl_containers.hpp
*	@brief Typedefs eastl containers with ncpp's default allocator.
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/prerequisites.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ncpp/mem/default_allocator.hpp>

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

	namespace containers {
        
        ////////////////////////////////////////////////////////////////////////////////////
        //  string
        ////////////////////////////////////////////////////////////////////////////////////
        template<typename F_char__ = char, typename F_allocator__ = mem::F_default_allocator>
        using TF_string = eastl::basic_string<F_char__, F_allocator__>;
        using F_string = TF_string<char>;
        using F_wstring = TF_string<wchar_t>;
            
        ////////////////////////////////////////////////////////////////////////////////////
        //  to string
        ////////////////////////////////////////////////////////////////////////////////////
        namespace internal {
                
            template<typename F_char__ = char, typename F_allocator__ = mem::F_default_allocator, typename F_value__ = int>
            struct TF_to_string_helper {
                
                
                
            };



            template<typename F_allocator__>
            struct TF_to_string_helper<char, F_allocator__, int> {

                using F_ctor_sprintf = typename TF_string<char, F_allocator__>::CtorSprintf;
                
                static NCPP_FORCE_INLINE TF_string<char, F_allocator__> to_string(int value)
                {
                    
                    static char format[] = "%d";
                        
                    TF_string<char, F_allocator__> result;
                    
                    result.append_sprintf(format, value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<char, F_allocator__, long> {

                using F_ctor_sprintf = typename TF_string<char, F_allocator__>::CtorSprintf;
                
                static NCPP_FORCE_INLINE TF_string<char, F_allocator__> to_string(long value)
                {
                    
                    static char format[] = "%ld";
                        
                    TF_string<char, F_allocator__> result;
                    
                    result.append_sprintf(format, value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<char, F_allocator__, long long> {

                using F_ctor_sprintf = typename TF_string<char, F_allocator__>::CtorSprintf;
                
                static NCPP_FORCE_INLINE TF_string<char, F_allocator__> to_string(long long value)
                {
                    
                    static char format[] = "%lld";
                        
                    TF_string<char, F_allocator__> result;
                    
                    result.append_sprintf(format, value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<char, F_allocator__, unsigned> {

                using F_ctor_sprintf = typename TF_string<char, F_allocator__>::CtorSprintf;
                
                static NCPP_FORCE_INLINE TF_string<char, F_allocator__> to_string(unsigned value)
                {
                    
                    static char format[] = "%u";
                        
                    TF_string<char, F_allocator__> result;
                    
                    result.append_sprintf(format, value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<char, F_allocator__, unsigned long> {

                using F_ctor_sprintf = typename TF_string<char, F_allocator__>::CtorSprintf;
                
                static NCPP_FORCE_INLINE TF_string<char, F_allocator__> to_string(unsigned long value)
                {
                    
                    static char format[] = "%lu";
                        
                    TF_string<char, F_allocator__> result;
                    
                    result.append_sprintf(format, value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<char, F_allocator__, unsigned long long> {

                using F_ctor_sprintf = typename TF_string<char, F_allocator__>::CtorSprintf;
                
                static NCPP_FORCE_INLINE TF_string<char, F_allocator__> to_string(unsigned long long value)
                {
                    
                    static char format[] = "%llu";
                        
                    TF_string<char, F_allocator__> result;
                    
                    result.append_sprintf(format, value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<char, F_allocator__, float> {

                using F_ctor_sprintf = typename TF_string<char, F_allocator__>::CtorSprintf;
                
                static NCPP_FORCE_INLINE TF_string<char, F_allocator__> to_string(float value)
                {
                    
                    static char format[] = "%f";
                        
                    TF_string<char, F_allocator__> result;
                    
                    result.append_sprintf(format, value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<char, F_allocator__, double> {

                using F_ctor_sprintf = typename TF_string<char, F_allocator__>::CtorSprintf;
                
                static NCPP_FORCE_INLINE TF_string<char, F_allocator__> to_string(double value)
                {
                    
                    static char format[] = "%f";
                        
                    TF_string<char, F_allocator__> result;
                    
                    result.append_sprintf(format, value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<char, F_allocator__, long double> {

                using F_ctor_sprintf = typename TF_string<char, F_allocator__>::CtorSprintf;
                
                static NCPP_FORCE_INLINE TF_string<char, F_allocator__> to_string(long double value)
                {
                    
                    static char format[] = "%Lf";
                        
                    TF_string<char, F_allocator__> result;
                    
                    result.append_sprintf(format, value);
                    
                    return eastl::move(result);
                }

            };

            

            template<typename F_allocator__>
            struct TF_to_string_helper<wchar_t, F_allocator__, int> {

                using F_ctor_sprintf = typename TF_string<wchar_t, F_allocator__>::CtorSprintf;
                
                static NCPP_FORCE_INLINE TF_string<wchar_t, F_allocator__> to_string(int value)
                {
                    
                    static wchar_t format[] = L"%d";
                        
                    TF_string<wchar_t, F_allocator__> result;
                    
                    result.append_sprintf(format, value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<wchar_t, F_allocator__, long> {

                using F_ctor_sprintf = typename TF_string<wchar_t, F_allocator__>::CtorSprintf;
                
                static NCPP_FORCE_INLINE TF_string<wchar_t, F_allocator__> to_string(long value)
                {
                    
                    static wchar_t format[] = L"%ld";
                        
                    TF_string<wchar_t, F_allocator__> result;
                    
                    result.append_sprintf(format, value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<wchar_t, F_allocator__, long long> {

                using F_ctor_sprintf = typename TF_string<wchar_t, F_allocator__>::CtorSprintf;
                
                static NCPP_FORCE_INLINE TF_string<wchar_t, F_allocator__> to_string(long long value)
                {
                    
                    static wchar_t format[] = L"%lld";
                        
                    TF_string<wchar_t, F_allocator__> result;
                    
                    result.append_sprintf(format, value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<wchar_t, F_allocator__, unsigned> {

                using F_ctor_sprintf = typename TF_string<wchar_t, F_allocator__>::CtorSprintf;
                
                static NCPP_FORCE_INLINE TF_string<wchar_t, F_allocator__> to_string(unsigned value)
                {
                    
                    static wchar_t format[] = L"%u";
                        
                    TF_string<wchar_t, F_allocator__> result;
                    
                    result.append_sprintf(format, value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<wchar_t, F_allocator__, unsigned long> {

                using F_ctor_sprintf = typename TF_string<wchar_t, F_allocator__>::CtorSprintf;
                
                static NCPP_FORCE_INLINE TF_string<wchar_t, F_allocator__> to_string(unsigned long value)
                {
                    
                    static wchar_t format[] = L"%lu";
                        
                    TF_string<wchar_t, F_allocator__> result;
                    
                    result.append_sprintf(format, value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<wchar_t, F_allocator__, unsigned long long> {

                using F_ctor_sprintf = typename TF_string<wchar_t, F_allocator__>::CtorSprintf;
                
                static NCPP_FORCE_INLINE TF_string<wchar_t, F_allocator__> to_string(unsigned long long value)
                {
                    
                    static wchar_t format[] = L"%llu";
                        
                    TF_string<wchar_t, F_allocator__> result;
                    
                    result.append_sprintf(format, value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<wchar_t, F_allocator__, float> {

                using F_ctor_sprintf = typename TF_string<wchar_t, F_allocator__>::CtorSprintf;
                
                static NCPP_FORCE_INLINE TF_string<wchar_t, F_allocator__> to_string(float value)
                {
                    
                    static wchar_t format[] = L"%f";
                        
                    TF_string<wchar_t, F_allocator__> result;
                    
                    result.append_sprintf(format, value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<wchar_t, F_allocator__, double> {

                using F_ctor_sprintf = typename TF_string<wchar_t, F_allocator__>::CtorSprintf;
                
                static NCPP_FORCE_INLINE TF_string<wchar_t, F_allocator__> to_string(double value)
                {
                    
                    static wchar_t format[] = L"%f";
                        
                    TF_string<wchar_t, F_allocator__> result;
                    
                    result.append_sprintf(format, value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<wchar_t, F_allocator__, long double> {

                using F_ctor_sprintf = typename TF_string<wchar_t, F_allocator__>::CtorSprintf;
                
                static NCPP_FORCE_INLINE TF_string<wchar_t, F_allocator__> to_string(long double value)
                {
                    
                    static wchar_t format[] = L"%Lf";
                        
                    TF_string<wchar_t, F_allocator__> result;
                    
                    result.append_sprintf(format, value);
                    
                    return eastl::move(result);
                }

            };

        }
        
        template<typename F_char__ = char, typename F_allocator__ = mem::F_default_allocator, typename F_value__ = int>
        NCPP_FORCE_INLINE TF_string<F_char__, F_allocator__> T_to_string(F_value__ value) {

            return internal::TF_to_string_helper<F_char__, F_allocator__, F_value__>::to_string(value);
        }
    
        NCPP_FORCE_INLINE F_string to_string(int value)
            { return T_to_string(value); }
        NCPP_FORCE_INLINE F_string to_string(long value)
            { return T_to_string(value); }
        NCPP_FORCE_INLINE F_string to_string(long long value)
            { return T_to_string(value); }
        NCPP_FORCE_INLINE F_string to_string(unsigned value)
            { return T_to_string(value); }
        NCPP_FORCE_INLINE F_string to_string(unsigned long value)
            { return T_to_string(value); }
        NCPP_FORCE_INLINE F_string to_string(unsigned long long value)
            { return T_to_string(value); }
        NCPP_FORCE_INLINE F_string to_string(float value)
            { return T_to_string(value); }
        NCPP_FORCE_INLINE F_string to_string(double value)
            { return T_to_string(value); }
        NCPP_FORCE_INLINE F_string to_string(long double value)
            { return T_to_string(value); }

        NCPP_FORCE_INLINE F_wstring to_wstring(int value)
            { return T_to_string<wchar_t>(value); }
        NCPP_FORCE_INLINE F_wstring to_wstring(long value)
            { return T_to_string<wchar_t>(value); }
        NCPP_FORCE_INLINE F_wstring to_wstring(long long value)
            { return T_to_string<wchar_t>(value); }
        NCPP_FORCE_INLINE F_wstring to_wstring(unsigned value)
            { return T_to_string<wchar_t>(value); }
        NCPP_FORCE_INLINE F_wstring to_wstring(unsigned long value)
            { return T_to_string<wchar_t>(value); }
        NCPP_FORCE_INLINE F_wstring to_wstring(unsigned long long value)
            { return T_to_string<wchar_t>(value); }
        NCPP_FORCE_INLINE F_wstring to_wstring(float value)
            { return T_to_string<wchar_t>(value); }
        NCPP_FORCE_INLINE F_wstring to_wstring(double value)
            { return T_to_string<wchar_t>(value); }
        NCPP_FORCE_INLINE F_wstring to_wstring(long double value)
            { return T_to_string<wchar_t>(value); }
        


        ////////////////////////////////////////////////////////////////////////////////////
        //  list, vector, deque
        ////////////////////////////////////////////////////////////////////////////////////
        template<typename F_item__, typename F_allocator__ = mem::F_default_allocator>
        using TF_vector = eastl::vector<F_item__, F_allocator__>;

        template<typename F_item__, typename F_allocator__ = mem::F_default_allocator>
        using TF_list = eastl::list<F_item__, F_allocator__>;

        template<typename F_item__, typename F_allocator__ = mem::F_default_allocator>
        using TF_deque = eastl::deque<F_item__, F_allocator__>;



        ////////////////////////////////////////////////////////////////////////////////////
        //  smart pointers
        ////////////////////////////////////////////////////////////////////////////////////
        template<typename F_item__, typename F_allocator__ = mem::F_default_allocator>
        using TF_shared_ptr = eastl::shared_ptr<F_item__>;


    
        ////////////////////////////////////////////////////////////////////////////////////
        //  hash
        ////////////////////////////////////////////////////////////////////////////////////
        template<typename F__>
        struct TF_hash : public eastl::hash<F__> {};
        
        template<typename F_allocator__>
        struct TF_hash<TF_string<char, F_allocator__>> {

            inline size_t operator()(const TF_string<char, F_allocator__>& x) const
            {
                const unsigned char* p = (const unsigned char*)x.c_str(); // To consider: limit p to at most 256 chars.
                unsigned int c, result = 2166136261U; // We implement an FNV-like string hash.
                while((c = *p++) != 0) // Using '!=' disables compiler warnings.
                    result = (result * 16777619) ^ c;
                return (size_t)result;
            }

        };
        
        template<typename F_allocator__>
        struct TF_hash<TF_string<wchar_t, F_allocator__>> {

            inline size_t operator()(const TF_string<wchar_t, F_allocator__>& x) const
            {
				const wchar_t* p = x.c_str();
				unsigned int c, result = 2166136261U;
				while((c = (unsigned int)*p++) != 0)
					result = (result * 16777619) ^ c;
				return (size_t)result;

            }

        };
    


        ////////////////////////////////////////////////////////////////////////////////////
        //  set, map, unordered set, unordered map
        ////////////////////////////////////////////////////////////////////////////////////
        template<typename F_item__, typename F_compare__ = eastl::less<F_item__>, typename F_allocator__ = mem::F_default_allocator>
        using TF_set = eastl::set<F_item__, F_compare__, F_allocator__>;

        template<typename F_key__, typename F_value__, typename F_compare__ = eastl::less<F_key__>, typename F_allocator__ = mem::F_default_allocator>
        using TF_map = eastl::map<F_key__, F_value__, F_compare__, F_allocator__>;

        template<typename F_item__, typename F_hash__ = TF_hash<F_item__>, typename F_predicate__ = eastl::equal_to<F_item__>, typename F_allocator__ = mem::F_default_allocator>
        using TF_unordered_set = eastl::unordered_set<F_item__, F_hash__, F_predicate__, F_allocator__>;

        template<typename F_key__, typename F_value__, typename F_hash__ = TF_hash<F_key__>, typename F_predicate__ = eastl::equal_to<F_key__>, typename F_allocator__ = mem::F_default_allocator>
        using TF_unordered_map = eastl::unordered_map<F_key__, F_value__, F_hash__, F_predicate__, F_allocator__>;



        ////////////////////////////////////////////////////////////////////////////////////
        //  queue, stack
        ////////////////////////////////////////////////////////////////////////////////////
        template<typename F_item__, typename F_deque__ = TF_deque<F_item__>>
        using TF_queue = eastl::queue<F_item__, F_deque__>;

        template<typename F_item__, typename F_vector__ = TF_vector<F_item__>>
        using TF_stack = eastl::stack<F_item__, F_vector__>;

    }

}
