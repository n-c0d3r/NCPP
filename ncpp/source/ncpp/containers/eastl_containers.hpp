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
#include <ncpp/mem/gtemp_allocator.hpp>

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
        using F_name = F_string;
        using F_text = F_wstring;

        template<typename F_char__ = char>
        using TG_string = eastl::basic_string<F_char__, mem::F_gtemp_allocator>;
        using G_string = TG_string<char>;
        using G_wstring = TG_string<wchar_t>;
        using G_name = G_string;
        using G_text = G_wstring;

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
                
                static inline TF_string<char, F_allocator__> to_string(int value)
                {

                    TF_string<char, F_allocator__> result(typename TF_string<char, F_allocator__>::CtorSprintf(), "%d", value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<char, F_allocator__, long> {

                using F_ctor_sprintf = typename TF_string<char, F_allocator__>::CtorSprintf;
                
                static inline TF_string<char, F_allocator__> to_string(long value)
                {
                        
                    TF_string<char, F_allocator__> result;
                    
                    result.append_sprintf("%ld", value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<char, F_allocator__, long long> {

                using F_ctor_sprintf = typename TF_string<char, F_allocator__>::CtorSprintf;
                
                static inline TF_string<char, F_allocator__> to_string(long long value)
                {
                        
                    TF_string<char, F_allocator__> result;
                    
                    result.append_sprintf("%lld", value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<char, F_allocator__, unsigned> {

                using F_ctor_sprintf = typename TF_string<char, F_allocator__>::CtorSprintf;
                
                static inline TF_string<char, F_allocator__> to_string(unsigned value)
                {
                        
                    TF_string<char, F_allocator__> result;
                    
                    result.append_sprintf("%u", value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<char, F_allocator__, unsigned long> {

                using F_ctor_sprintf = typename TF_string<char, F_allocator__>::CtorSprintf;
                
                static inline TF_string<char, F_allocator__> to_string(unsigned long value)
                {
                        
                    TF_string<char, F_allocator__> result;
                    
                    result.append_sprintf("%lu", value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<char, F_allocator__, unsigned long long> {

                using F_ctor_sprintf = typename TF_string<char, F_allocator__>::CtorSprintf;
                
                static inline TF_string<char, F_allocator__> to_string(unsigned long long value)
                {
                        
                    TF_string<char, F_allocator__> result;
                    
                    result.append_sprintf("%llu", value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<char, F_allocator__, float> {

                using F_ctor_sprintf = typename TF_string<char, F_allocator__>::CtorSprintf;
                
                static inline TF_string<char, F_allocator__> to_string(float value)
                {
                        
                    TF_string<char, F_allocator__> result;
                    
                    result.append_sprintf("%f", value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<char, F_allocator__, double> {

                using F_ctor_sprintf = typename TF_string<char, F_allocator__>::CtorSprintf;
                
                static inline TF_string<char, F_allocator__> to_string(double value)
                {
                        
                    TF_string<char, F_allocator__> result;
                    
                    result.append_sprintf("%f", value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<char, F_allocator__, long double> {

                using F_ctor_sprintf = typename TF_string<char, F_allocator__>::CtorSprintf;
                
                static inline TF_string<char, F_allocator__> to_string(long double value)
                {
                        
                    TF_string<char, F_allocator__> result;
                    
                    result.append_sprintf("%Lf", value);
                    
                    return eastl::move(result);
                }

            };
        
            template<typename F_allocator__>
            struct TF_to_string_helper<char, F_allocator__, TF_string<wchar_t, F_allocator__>> {

                using F_ctor_sprintf = typename TF_string<char, F_allocator__>::CtorSprintf;
                
                static inline TF_string<char, F_allocator__> to_string(const TF_string<wchar_t, F_allocator__>& value)
                {
                        
                    TF_string<char, F_allocator__> result;
                    
                    size_t n = value.length();
                    
                    result.resize(n);
                    
                    for (size_t i = 0; i < n; ++i)
                        result[i] = value[i];
                    
                    return eastl::move(result);
                }

            };
        
            template<typename F_allocator__>
            struct TF_to_string_helper<char, F_allocator__, const wchar_t*> {

                using F_ctor_sprintf = typename TF_string<char, F_allocator__>::CtorSprintf;
                
                static NCPP_FORCE_INLINE TF_string<char, F_allocator__> to_string(const wchar_t* value)
                {
                    
                    return TF_to_string_helper<char, F_allocator__, TF_string<wchar_t, F_allocator__>>::to_string(value);
                }

            };
            
            template<typename F_allocator__>
            struct TF_to_string_helper<char, F_allocator__, TF_string<char, F_allocator__>> {

                using F_ctor_sprintf = typename TF_string<char, F_allocator__>::CtorSprintf;
                
                static NCPP_FORCE_INLINE TF_string<char, F_allocator__> to_string(const TF_string<char, F_allocator__>& value)
                {
                    
                    return value;
                }

            };
        
            template<typename F_allocator__>
            struct TF_to_string_helper<char, F_allocator__, const char*> {

                using F_ctor_sprintf = typename TF_string<char, F_allocator__>::CtorSprintf;
                
                static NCPP_FORCE_INLINE TF_string<char, F_allocator__> to_string(const char* value)
                {
                    
                    return value;
                }

            };

                

            template<typename F_allocator__>
            struct TF_to_string_helper<wchar_t, F_allocator__, int> {

                using F_ctor_sprintf = typename TF_string<wchar_t, F_allocator__>::CtorSprintf;
                
                static inline TF_string<wchar_t, F_allocator__> to_string(int value)
                {
                        
                    TF_string<wchar_t, F_allocator__> result;
                    
                    result.append_sprintf(L"%d", value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<wchar_t, F_allocator__, long> {

                using F_ctor_sprintf = typename TF_string<wchar_t, F_allocator__>::CtorSprintf;
                
                static inline TF_string<wchar_t, F_allocator__> to_string(long value)
                {
                        
                    TF_string<wchar_t, F_allocator__> result;
                    
                    result.append_sprintf(L"%ld", value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<wchar_t, F_allocator__, long long> {

                using F_ctor_sprintf = typename TF_string<wchar_t, F_allocator__>::CtorSprintf;
                
                static inline TF_string<wchar_t, F_allocator__> to_string(long long value)
                {
                        
                    TF_string<wchar_t, F_allocator__> result;
                    
                    result.append_sprintf(L"%lld", value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<wchar_t, F_allocator__, unsigned> {

                using F_ctor_sprintf = typename TF_string<wchar_t, F_allocator__>::CtorSprintf;
                
                static inline TF_string<wchar_t, F_allocator__> to_string(unsigned value)
                {
                        
                    TF_string<wchar_t, F_allocator__> result;
                    
                    result.append_sprintf(L"%u", value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<wchar_t, F_allocator__, unsigned long> {

                using F_ctor_sprintf = typename TF_string<wchar_t, F_allocator__>::CtorSprintf;
                
                static inline TF_string<wchar_t, F_allocator__> to_string(unsigned long value)
                {
                        
                    TF_string<wchar_t, F_allocator__> result;
                    
                    result.append_sprintf(L"%lu", value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<wchar_t, F_allocator__, unsigned long long> {

                using F_ctor_sprintf = typename TF_string<wchar_t, F_allocator__>::CtorSprintf;
                
                static inline TF_string<wchar_t, F_allocator__> to_string(unsigned long long value)
                {
                        
                    TF_string<wchar_t, F_allocator__> result;
                    
                    result.append_sprintf(L"%llu", value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<wchar_t, F_allocator__, float> {

                using F_ctor_sprintf = typename TF_string<wchar_t, F_allocator__>::CtorSprintf;
                
                static inline TF_string<wchar_t, F_allocator__> to_string(float value)
                {
                        
                    TF_string<wchar_t, F_allocator__> result;
                    
                    result.append_sprintf(L"%f", value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<wchar_t, F_allocator__, double> {

                using F_ctor_sprintf = typename TF_string<wchar_t, F_allocator__>::CtorSprintf;
                
                static inline TF_string<wchar_t, F_allocator__> to_string(double value)
                {
                        
                    TF_string<wchar_t, F_allocator__> result;
                    
                    result.append_sprintf(L"%f", value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<wchar_t, F_allocator__, long double> {

                using F_ctor_sprintf = typename TF_string<wchar_t, F_allocator__>::CtorSprintf;
                
                static inline TF_string<wchar_t, F_allocator__> to_string(long double value)
                {
                        
                    TF_string<wchar_t, F_allocator__> result;
                    
                    result.append_sprintf(L"%Lf", value);
                    
                    return eastl::move(result);
                }

            };

            template<typename F_allocator__>
            struct TF_to_string_helper<wchar_t, F_allocator__, TF_string<char, F_allocator__>> {

                using F_ctor_sprintf = typename TF_string<wchar_t, F_allocator__>::CtorSprintf;
                
                static inline TF_string<wchar_t, F_allocator__> to_string(const TF_string<char, F_allocator__>& value)
                {
                        
                    TF_string<wchar_t, F_allocator__> result;
                    
                    size_t n = value.length();
                    
                    result.resize(n);
                    
                    for (size_t i = 0; i < n; ++i)
                        result[i] = value[i];
                    
                    return eastl::move(result);
                }

            };
        
            template<typename F_allocator__>
            struct TF_to_string_helper<wchar_t, F_allocator__, const char*> {

                using F_ctor_sprintf = typename TF_string<wchar_t, F_allocator__>::CtorSprintf;
                
                static NCPP_FORCE_INLINE TF_string<wchar_t, F_allocator__> to_string(const char* value)
                {
                    
                    return TF_to_string_helper<wchar_t, F_allocator__, TF_string<char, F_allocator__>>::to_string(value);
                }

            };
        
            template<typename F_allocator__>
            struct TF_to_string_helper<wchar_t, F_allocator__, TF_string<wchar_t, F_allocator__>> {

                using F_ctor_sprintf = typename TF_string<wchar_t, F_allocator__>::CtorSprintf;
                
                static NCPP_FORCE_INLINE TF_string<wchar_t, F_allocator__> to_string(const TF_string<wchar_t, F_allocator__>& value)
                {
                    
                    return value;
                }

            };
        
            template<typename F_allocator__>
            struct TF_to_string_helper<wchar_t, F_allocator__, const wchar_t*> {

                using F_ctor_sprintf = typename TF_string<wchar_t, F_allocator__>::CtorSprintf;
                
                static NCPP_FORCE_INLINE TF_string<wchar_t, F_allocator__> to_string(const wchar_t* value)
                {
                    
                    return value;
                }

            };

        }
        
        template<typename F_char__ = char, typename F_allocator__ = mem::F_default_allocator, typename F_value__ = int>
        inline TF_string<F_char__, F_allocator__> T_to_string(const F_value__& value) {

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
        NCPP_FORCE_INLINE F_string to_string(const TF_string<wchar_t>& value)
            { return T_to_string<char, mem::F_default_allocator, F_wstring>(value); }
        NCPP_FORCE_INLINE F_string to_string(const wchar_t* value)
            { return T_to_string<char, mem::F_default_allocator, const wchar_t*>(value); }
        NCPP_FORCE_INLINE F_string to_string(const TF_string<char>& value)
            { return T_to_string<char, mem::F_default_allocator, F_string>(value); }
        NCPP_FORCE_INLINE F_string to_string(const char* value)
            { return T_to_string<char, mem::F_default_allocator, const char*>(value); }

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
        NCPP_FORCE_INLINE F_wstring to_wstring(const TF_string<char>& value)
            { return T_to_string<wchar_t, mem::F_default_allocator, F_string>(value); }
        NCPP_FORCE_INLINE F_wstring to_wstring(const char* value)
            { return T_to_string<wchar_t, mem::F_default_allocator, const char*>(value); }
        NCPP_FORCE_INLINE F_wstring to_wstring(const TF_string<wchar_t>& value)
            { return T_to_string<wchar_t, mem::F_default_allocator, F_wstring>(value); }
        NCPP_FORCE_INLINE F_wstring to_wstring(const wchar_t* value)
            { return T_to_string<wchar_t, mem::F_default_allocator, const wchar_t*>(value); }

        NCPP_FORCE_INLINE G_string G_to_string(int value)
            { return T_to_string<char, mem::F_gtemp_allocator>(value); }
        NCPP_FORCE_INLINE G_string G_to_string(long value)
            { return T_to_string<char, mem::F_gtemp_allocator>(value); }
        NCPP_FORCE_INLINE G_string G_to_string(long long value)
            { return T_to_string<char, mem::F_gtemp_allocator>(value); }
        NCPP_FORCE_INLINE G_string G_to_string(unsigned value)
            { return T_to_string<char, mem::F_gtemp_allocator>(value); }
        NCPP_FORCE_INLINE G_string G_to_string(unsigned long value)
            { return T_to_string<char, mem::F_gtemp_allocator>(value); }
        NCPP_FORCE_INLINE G_string G_to_string(unsigned long long value)
            { return T_to_string<char, mem::F_gtemp_allocator>(value); }
        NCPP_FORCE_INLINE G_string G_to_string(float value)
            { return T_to_string<char, mem::F_gtemp_allocator>(value); }
        NCPP_FORCE_INLINE G_string G_to_string(double value)
            { return T_to_string<char, mem::F_gtemp_allocator>(value); }
        NCPP_FORCE_INLINE G_string G_to_string(long double value)
            { return T_to_string<char, mem::F_gtemp_allocator>(value); }
        NCPP_FORCE_INLINE G_string G_to_string(const TG_string<wchar_t>& value)
            { return T_to_string<char, mem::F_gtemp_allocator, G_wstring>(value); }
        NCPP_FORCE_INLINE G_string G_to_string(const wchar_t* value)
            { return T_to_string<char, mem::F_gtemp_allocator, const wchar_t*>(value); }
        NCPP_FORCE_INLINE G_string G_to_string(const TG_string<char>& value)
            { return T_to_string<char, mem::F_gtemp_allocator, G_string>(value); }
        NCPP_FORCE_INLINE G_string G_to_string(const char* value)
            { return T_to_string<char, mem::F_gtemp_allocator, const char*>(value); }

        NCPP_FORCE_INLINE G_wstring G_to_wstring(int value)
            { return T_to_string<wchar_t, mem::F_gtemp_allocator>(value); }
        NCPP_FORCE_INLINE G_wstring G_to_wstring(long value)
            { return T_to_string<wchar_t, mem::F_gtemp_allocator>(value); }
        NCPP_FORCE_INLINE G_wstring G_to_wstring(long long value)
            { return T_to_string<wchar_t, mem::F_gtemp_allocator>(value); }
        NCPP_FORCE_INLINE G_wstring G_to_wstring(unsigned value)
            { return T_to_string<wchar_t, mem::F_gtemp_allocator>(value); }
        NCPP_FORCE_INLINE G_wstring G_to_wstring(unsigned long value)
            { return T_to_string<wchar_t, mem::F_gtemp_allocator>(value); }
        NCPP_FORCE_INLINE G_wstring G_to_wstring(unsigned long long value)
            { return T_to_string<wchar_t, mem::F_gtemp_allocator>(value); }
        NCPP_FORCE_INLINE G_wstring G_to_wstring(float value)
            { return T_to_string<wchar_t, mem::F_gtemp_allocator>(value); }
        NCPP_FORCE_INLINE G_wstring G_to_wstring(double value)
            { return T_to_string<wchar_t, mem::F_gtemp_allocator>(value); }
        NCPP_FORCE_INLINE G_wstring G_to_wstring(long double value)
            { return T_to_string<wchar_t, mem::F_gtemp_allocator>(value); }
        NCPP_FORCE_INLINE G_wstring G_to_wstring(const TG_string<char>& value)
            { return T_to_string<wchar_t, mem::F_gtemp_allocator, G_string>(value); }
        NCPP_FORCE_INLINE G_wstring G_to_wstring(const char* value)
            { return T_to_string<wchar_t, mem::F_gtemp_allocator, const char*>(value); }
        NCPP_FORCE_INLINE G_wstring G_to_wstring(const TG_string<wchar_t>& value)
            { return T_to_string<wchar_t, mem::F_gtemp_allocator, G_wstring>(value); }
        NCPP_FORCE_INLINE G_wstring G_to_wstring(const wchar_t* value)
            { return T_to_string<wchar_t, mem::F_gtemp_allocator, const wchar_t*>(value); }



        ////////////////////////////////////////////////////////////////////////////////////
        //  list, vector, deque
        ////////////////////////////////////////////////////////////////////////////////////
        template<typename F_item__, typename F_allocator__ = mem::F_default_allocator>
        using TF_vector = eastl::vector<F_item__, F_allocator__>;
        template<typename F_item__>
        using TG_vector = eastl::vector<F_item__, mem::F_gtemp_allocator>;

        template<typename F_item__, typename F_allocator__ = mem::F_default_allocator>
        using TF_list = eastl::list<F_item__, F_allocator__>;
        template<typename F_item__>
        using TG_list = eastl::list<F_item__, mem::F_gtemp_allocator>;

        template<typename F_item__, typename F_allocator__ = mem::F_default_allocator>
        using TF_deque = eastl::deque<F_item__, F_allocator__>;
        template<typename F_item__>
        using TG_deque = eastl::deque<F_item__, mem::F_gtemp_allocator>;



        ////////////////////////////////////////////////////////////////////////////////////
        //  smart pointers
        ////////////////////////////////////////////////////////////////////////////////////
        template<typename F_item__>
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
        template<typename F_item__, typename F_compare__ = eastl::less<F_item__>>
        using TG_set = eastl::set<F_item__, F_compare__, mem::F_gtemp_allocator>;

        template<typename F_key__, typename F_value__, typename F_compare__ = eastl::less<F_key__>, typename F_allocator__ = mem::F_default_allocator>
        using TF_map = eastl::map<F_key__, F_value__, F_compare__, F_allocator__>;
        template<typename F_key__, typename F_value__, typename F_compare__ = eastl::less<F_key__>>
        using TG_map = eastl::map<F_key__, F_value__, F_compare__, mem::F_gtemp_allocator>;

        template<typename F_item__, typename F_hash__ = TF_hash<F_item__>, typename F_predicate__ = eastl::equal_to<F_item__>, typename F_allocator__ = mem::F_default_allocator>
        using TF_unordered_set = eastl::unordered_set<F_item__, F_hash__, F_predicate__, F_allocator__>;
        template<typename F_item__, typename F_hash__ = TF_hash<F_item__>, typename F_predicate__ = eastl::equal_to<F_item__>>
        using TG_unordered_set = eastl::unordered_set<F_item__, F_hash__, F_predicate__, mem::F_gtemp_allocator>;

        template<typename F_key__, typename F_value__, typename F_hash__ = TF_hash<F_key__>, typename F_predicate__ = eastl::equal_to<F_key__>, typename F_allocator__ = mem::F_default_allocator>
        using TF_unordered_map = eastl::unordered_map<F_key__, F_value__, F_hash__, F_predicate__, F_allocator__>;
        template<typename F_key__, typename F_value__, typename F_hash__ = TF_hash<F_key__>, typename F_predicate__ = eastl::equal_to<F_key__>>
        using TG_unordered_map = eastl::unordered_map<F_key__, F_value__, F_hash__, F_predicate__, mem::F_gtemp_allocator>;



        ////////////////////////////////////////////////////////////////////////////////////
        //  queue, stack
        ////////////////////////////////////////////////////////////////////////////////////
        template<typename F_item__, typename F_deque__ = TF_deque<F_item__>>
        using TF_queue = eastl::queue<F_item__, F_deque__>;
        template<typename F_item__, typename G_deque__ = TG_deque<F_item__>>
        using TG_queue = eastl::queue<F_item__, G_deque__>;

        template<typename F_item__, typename F_vector__ = TF_vector<F_item__>>
        using TF_stack = eastl::stack<F_item__, F_vector__>;
        template<typename F_item__, typename G_vector__ = TG_vector<F_item__>>
        using TG_stack = eastl::stack<F_item__, G_vector__>;

    }

}
