#pragma once

/** @file ncpp/containers/view.hpp
*	@brief Implements view.
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

#include <ncpp/containers/binding_helper.hpp>
#include <ncpp/mem/general_allocator.hpp>
#include <ncpp/utilities/iterator.hpp>

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

        template<typename F__>
        static constexpr b8 T_is_viewable_container_v = (
            !T_is_has_container_allocator_v<F__>
            || mem::T_can_be_general_allocator_v<
                TF_container_allocator<F__>
            >
        );

        template<typename F1__, typename F2__>
        static constexpr b8 T_is_same_viewable_container_v = (
            T_is_same_container_v<F1__, F2__>
            && T_is_viewable_container_v<F1__>
        );



        template<typename F_container__>
        class TF_view {

        public:
            using F_container = F_container__;

            static_assert(
                T_is_viewable_container_v<F_container__>,
                "non-viewable container"
            );



        private:
            const F_container* container_p_ = 0;

        public:
            NCPP_FORCE_INLINE const F_container* container_p() const { return container_p_; }
            NCPP_FORCE_INLINE const F_container& container() const { return *container_p_; }



        public:
            NCPP_FORCE_INLINE TF_view() = default;



        public:
            template<
                typename F_other_container__,
                std::enable_if_t<T_is_same_viewable_container_v<F_container, F_other_container__>, i32> = 0
            >
            NCPP_FORCE_INLINE TF_view(const F_other_container__& other_container) noexcept :
                container_p_(reinterpret_cast<const F_container*>(&other_container))
            {



            }

            template<
                typename F_other_container__,
                std::enable_if_t<T_is_same_viewable_container_v<F_container, F_other_container__>, i32> = 0
            >
            NCPP_FORCE_INLINE TF_view& operator = (const F_other_container__& other_container) noexcept {

                container_p_ = reinterpret_cast<const F_container*>(&other_container);

                return *this;
            }



        public:
            template<
                typename F_other_container__,
                std::enable_if_t<T_is_same_viewable_container_v<F_container, F_other_container__>, i32> = 0
            >
            NCPP_FORCE_INLINE TF_view(const TF_view<F_other_container__>& other_view) noexcept :
                    container_p_(reinterpret_cast<const F_container*>(other_view.container_p_()))
            {



            }

            template<
                typename F_other_container__,
                std::enable_if_t<T_is_same_viewable_container_v<F_container, F_other_container__>, i32> = 0
            >
            NCPP_FORCE_INLINE TF_view& operator = (const TF_view<F_other_container__>& other_view) noexcept {

                container_p_ = reinterpret_cast<const F_container*>(other_view.container_p_());

                return *this;
            }



        public:
            template<
                typename F_other_container__,
                std::enable_if_t<T_is_same_viewable_container_v<F_container, F_other_container__>, i32> = 0
            >
            NCPP_FORCE_INLINE TF_view(TF_view<F_other_container__>&& other_view) noexcept :
                    container_p_(reinterpret_cast<const F_container*>(other_view.container_p_()))
            {

                other_view.reset();

            }

            template<
                typename F_other_container__,
                std::enable_if_t<T_is_same_viewable_container_v<F_container, F_other_container__>, i32> = 0
            >
            NCPP_FORCE_INLINE TF_view& operator = (TF_view<F_other_container__>&& other_view) noexcept {

                container_p_ = reinterpret_cast<const F_container*>(other_view.container_p_());

                other_view.reset();

                return *this;
            }



        public:
            NCPP_FORCE_INLINE const F_container* operator->() const noexcept {

                return container_p_;
            }
            NCPP_FORCE_INLINE const F_container& operator*() const noexcept {

                return *container_p_;
            }

            template<
                typename F_arg__,
                typename F_default_return__ = std::remove_const_t<
                    std::remove_reference_t<
                        decltype((*container_p_)[std::declval<F_arg__>()])
                    >
                >
            >
            NCPP_FORCE_INLINE utilities::TF_nth_template_arg_t<
                sizeof(F_default_return__) <= sizeof(void*),
                const F_default_return__&,
                F_default_return__
            > operator[](F_arg__ arg) const {

                return (*container_p_)[arg];
            }

            template<
                typename F_other_container__,
                std::enable_if_t<T_is_same_viewable_container_v<F_container, F_other_container__>, i32> = 0
            >
            NCPP_FORCE_INLINE operator F_other_container__() const {

                return *reinterpret_cast<const F_other_container__*>(container_p_);
            }



        private:
            template<typename F__, std::enable_if_t<utilities::T_is_has_begin_const_v<F__>, i32> = 0>
            NCPP_FORCE_INLINE auto T_begin_internal() const {

                return container_p_->begin();
            }
            template<typename F__, std::enable_if_t<!utilities::T_is_has_begin_const_v<F__>, i32> = 0>
            NCPP_FORCE_INLINE void T_begin_internal() const {

            }
            template<typename F__, std::enable_if_t<utilities::T_is_has_cbegin_v<F__>, i32> = 0>
            NCPP_FORCE_INLINE auto T_cbegin_internal() const {

                return container_p_->cbegin();
            }
            template<typename F__, std::enable_if_t<!utilities::T_is_has_cbegin_v<F__>, i32> = 0>
            NCPP_FORCE_INLINE void T_cbegin_internal() const {

            }
            template<typename F__, std::enable_if_t<utilities::T_is_has_end_const_v<F__>, i32> = 0>
            NCPP_FORCE_INLINE auto T_end_internal() const {

                return container_p_->end();
            }
            template<typename F__, std::enable_if_t<!utilities::T_is_has_end_const_v<F__>, i32> = 0>
            NCPP_FORCE_INLINE void T_end_internal() const {

            }
            template<typename F__, std::enable_if_t<utilities::T_is_has_cend_v<F__>, i32> = 0>
            NCPP_FORCE_INLINE auto T_cend_internal() const {

                return container_p_->cend();
            }
            template<typename F__, std::enable_if_t<!utilities::T_is_has_cend_v<F__>, i32> = 0>
            NCPP_FORCE_INLINE void T_cend_internal() const {

            }

        public:
            NCPP_FORCE_INLINE auto begin() const {

                return T_begin_internal<F_container>();
            }
            NCPP_FORCE_INLINE auto cbegin() const {

                return T_cbegin_internal<F_container>();
            }
            NCPP_FORCE_INLINE auto end() const {

                return T_end_internal<F_container>();
            }
            NCPP_FORCE_INLINE auto cend() const {

                return T_cend_internal<F_container>();
            }



        public:
            NCPP_FORCE_INLINE void reset() noexcept {

                container_p_ = 0;
            }

        };



        template<
            typename F_container__,
            std::enable_if_t<
                T_is_viewable_container_v<F_container__>,
                i32
            > = 0
        >
        NCPP_FORCE_INLINE TF_view<F_container__> T_to_view(const F_container__& container) noexcept {

            return container;
        }
       
    }

}