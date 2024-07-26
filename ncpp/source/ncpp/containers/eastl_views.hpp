#pragma once

/** @file ncpp/containers/eastl_views.hpp
*	@brief Typedefs eastl views.
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

#include <ncpp/containers/eastl_containers.hpp>
#include <ncpp/containers/eastl_bindings.hpp>
#include <ncpp/containers/view.hpp>

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
        template<typename F_char__ = char>
        using TV_string = TF_view<TG_string<F_char__>>;
        using V_string = TV_string<char>;
        using V_wstring = TV_string<wchar_t>;
        using V_name = V_string;
        using V_text = V_wstring;



        ////////////////////////////////////////////////////////////////////////////////////
        //  array, span
        ////////////////////////////////////////////////////////////////////////////////////
        template<typename F_item__, sz size__>
        using TV_array = TF_view<TG_array<F_item__, size__>>;
        template<typename F_item__>
        using TV_span = TF_view<TG_span<F_item__>>;
        template<typename F_item__>
        using TV_initializer_list = TF_view<TG_initializer_list<F_item__>>;



        ////////////////////////////////////////////////////////////////////////////////////
        //  list, vector, deque
        ////////////////////////////////////////////////////////////////////////////////////
        template<typename F_item__>
        using TV_vector = TF_view<TG_vector<F_item__>>;

        template<typename F_item__>
        using TV_list = TF_view<TG_list<F_item__>>;

        template<typename F_item__, unsigned subarray_size__ = DEQUE_DEFAULT_SUBARRAY_SIZE(F_item__)>
        using TV_deque = TF_view<TG_deque<F_item__, subarray_size__>>;



		////////////////////////////////////////////////////////////////////////////////////
		//  fixed_vector
		////////////////////////////////////////////////////////////////////////////////////
		template<typename F_item__, sz size__, b8 enable_overflow__ = true>
		using TV_fixed_vector = TF_view<TG_fixed_vector<F_item__, size__, enable_overflow__>>;
    


        ////////////////////////////////////////////////////////////////////////////////////
        //  set, map, unordered set, unordered map
        ////////////////////////////////////////////////////////////////////////////////////
        template<typename F_item__, typename F_compare__ = eastl::less<F_item__>>
        using TV_set = TF_view<TG_set<F_item__, F_compare__>>;

        template<typename F_key__, typename F_value__, typename F_compare__ = eastl::less<F_key__>>
        using TV_map = TF_view<TG_map<F_key__, F_value__, F_compare__>>;

        template<typename F_item__, typename F_hash__ = TF_hash<F_item__>, typename F_predicate__ = eastl::equal_to<F_item__>>
        using TV_unordered_set = TF_view<TG_unordered_set<F_item__, F_hash__, F_predicate__>>;

        template<typename F_key__, typename F_value__, typename F_hash__ = TF_hash<F_key__>, typename F_predicate__ = eastl::equal_to<F_key__>>
        using TV_unordered_map = TF_view<TG_unordered_map<F_key__, F_value__, F_hash__, F_predicate__>>;

        template<typename F_key__, typename F_value__, typename F_compare__ = eastl::less<F_key__>>
        using TV_multimap = TF_view<TG_multimap<F_key__, F_value__, F_compare__>>;

        template<typename F_key__, typename F_value__, typename F_hash__ = TF_hash<F_key__>, typename F_predicate__ = eastl::equal_to<F_key__>>
        using TV_unordered_multimap = TF_view<TG_unordered_multimap<F_key__, F_value__, F_hash__, F_predicate__>>;



        ////////////////////////////////////////////////////////////////////////////////////
        //  queue, stack
        ////////////////////////////////////////////////////////////////////////////////////
        template<typename F_item__, typename F_deque__ = TF_deque<F_item__>>
        using TV_queue = TF_view<TG_queue<F_item__, F_deque__>>;

        template<typename F_item__, typename F_vector__ = TF_vector<F_item__>>
        using TV_stack = TF_view<TG_stack<F_item__, F_vector__>>;

    }

}
