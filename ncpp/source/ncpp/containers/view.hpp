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
#include <ncpp/containers/eastl_containers.hpp>
#include <ncpp/mem/general_allocator.hpp>
#include <ncpp/utilities/value_type.hpp>
#include <ncpp/utilities/item_type.hpp>
#include <ncpp/utilities/key_type.hpp>
#include <ncpp/utilities/node_type.hpp>
#include <ncpp/utilities/iterator.hpp>
#include <ncpp/utilities/sizeof.hpp>
#include <ncpp/utilities/nth_template_arg.hpp>
#include <ncpp/utilities/mem_wrap.hpp>
#include <ncpp/iostream.hpp>
#include <ncpp/rtti/rtti_flag.hpp>

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

        template<sz allocator_size__>
        struct TF_view_with_allocator_flag {};

        struct F_view_flag {};



        template<typename F1__, typename F2__>
        static constexpr b8 T_is_same_viewable_container_v = (
            T_is_same_container_v<F1__, F2__>
            && (utilities::T_sizeof<TF_container_allocator<F1__>> == utilities::T_sizeof<TF_container_allocator<F2__>>)
        );



        template<typename F_container__>
        class TF_view {

        public:
            using F_this = TF_view<F_container__>;
            using F_container = F_container__;
            using F_allocator = TF_container_allocator<F_container__>;

            NCPP_RTTI_IMPLEMENT_FLAG(F_this, TF_view_with_allocator_flag<utilities::T_sizeof<F_allocator>>);
            NCPP_RTTI_IMPLEMENT_FLAG(F_this, F_view_flag);



        private:
            const F_container* container_p_ = 0;

#ifdef NCPP_DEBUG
            au64* owner_counter_p_ = 0;
            b8 is_root_owner_ = false;
#endif

        public:
            NCPP_FORCE_INLINE const F_container* container_p() const { return container_p_; }
            NCPP_FORCE_INLINE const F_container& container() const { return *container_p_; }

            NCPP_FORCE_INLINE b8 is_null() const { return (container_p_ == 0); }
            NCPP_FORCE_INLINE b8 is_valid() const { return (container_p_ != 0); }

#ifdef NCPP_DEBUG
            NCPP_FORCE_INLINE au64* owner_counter_p() const {

                return (au64*)owner_counter_p_;
            }
#endif



        public:
            NCPP_FORCE_INLINE TF_view() = default;

            NCPP_FORCE_INLINE ~TF_view() NCPP_ENABLE_IF_RELEASE(noexcept) {

                reset();

            }



        public:
            template<
                typename F__,
                std::enable_if_t<!T_is_same_viewable_container_v<F_container, F__>, i32> = 0
            >
            NCPP_FORCE_INLINE TF_view(const F__& x, const utilities::TF_mem_wrap<F_container>& container = utilities::TF_mem_wrap<F_container>{}) :
                container_p_((const F_container*)&container)

#ifdef NCPP_DEBUG
                ,
                owner_counter_p_(new au64(1)),
                is_root_owner_(true)
#endif
            {

                new ((F_container*)&container) F_container(x);

            }
            template<typename F_fake_container__ = F_container, std::enable_if_t<!std::is_same_v<void, utilities::TF_key<F_fake_container__>>, i32> = 0>
            NCPP_FORCE_INLINE TF_view(std::initializer_list<utilities::TF_key<F_container>> x, const utilities::TF_mem_wrap<F_container>& container = utilities::TF_mem_wrap<F_container>{}) :
                container_p_((const F_container*)&container)

#ifdef NCPP_DEBUG
                ,
                owner_counter_p_(new au64(1)),
                is_root_owner_(true)
#endif
            {

                new ((F_container*)&container) F_container(x);

            }
            template<typename F_fake_container__ = F_container, std::enable_if_t<!std::is_same_v<void, utilities::TF_value<F_fake_container__>>, i32> = 0>
            NCPP_FORCE_INLINE TF_view(std::initializer_list<utilities::TF_value<F_container>> x, const utilities::TF_mem_wrap<F_container>& container = utilities::TF_mem_wrap<F_container>{}) :
                container_p_((const F_container*)&container)

#ifdef NCPP_DEBUG
                ,
                owner_counter_p_(new au64(1)),
                is_root_owner_(true)
#endif
            {

                new ((F_container*)&container) F_container(x);

            }
            template<typename F_fake_container__ = F_container, std::enable_if_t<!std::is_same_v<void, utilities::TF_node<F_fake_container__>>, i32> = 0>
            NCPP_FORCE_INLINE TF_view(std::initializer_list<utilities::TF_node<F_container>> x, const utilities::TF_mem_wrap<F_container>& container = utilities::TF_mem_wrap<F_container>{}) :
                container_p_((const F_container*)&container)

#ifdef NCPP_DEBUG
                ,
                owner_counter_p_(new au64(1)),
                is_root_owner_(true)
#endif
            {

                new ((F_container*)&container) F_container(x);

            }
            template<typename F_fake_container__ = F_container, std::enable_if_t<!std::is_same_v<void, utilities::TF_item<F_fake_container__>>, i32> = 0>
            NCPP_FORCE_INLINE TF_view(std::initializer_list<utilities::TF_item<F_container>> x, const utilities::TF_mem_wrap<F_container>& container = utilities::TF_mem_wrap<F_container>{}) :
                container_p_((const F_container*)&container)

#ifdef NCPP_DEBUG
                ,
                owner_counter_p_(new au64(1)),
                is_root_owner_(true)
#endif
            {

                new ((F_container*)&container) F_container(x);

            }



        public:
            template<
                typename F_other_container__,
                std::enable_if_t<T_is_same_viewable_container_v<F_container, F_other_container__>, i32> = 0
            >
            NCPP_FORCE_INLINE operator const F_other_container__&() const noexcept {

                return *reinterpret_cast<const F_other_container__*>(container_p_);
            }



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
            NCPP_FORCE_INLINE TF_view& operator = (const F_other_container__& other_container) noexcept
            {

                container_p_ = reinterpret_cast<const F_container*>(&other_container);

                return *this;
            }



        public:
            template<
                class F_other_view__,
                typename = decltype(T_is_same_viewable_container_v<F_container, typename F_other_view__::F_container>)
            >
            NCPP_FORCE_INLINE TF_view(const F_other_view__& other_view) NCPP_ENABLE_IF_RELEASE(noexcept) :
                container_p_(reinterpret_cast<const F_container*>(other_view.container_p()))
            {

                NCPP_ENABLE_IF_DEBUG(T_increase_owner_counter((F_other_view__&)other_view));

            }
            template<
                class F_other_view__,
                typename = decltype(T_is_same_viewable_container_v<F_container, typename F_other_view__::F_container>)
            >
            NCPP_FORCE_INLINE TF_view& operator = (const F_other_view__& other_view) NCPP_ENABLE_IF_RELEASE(noexcept) {

                container_p_ = reinterpret_cast<const F_container*>(other_view.container_p());

                NCPP_ENABLE_IF_DEBUG(T_increase_owner_counter((F_other_view__&)other_view));

                return *this;
            }



        public:
            template<
                class F_other_view__,
                typename = decltype(T_is_same_viewable_container_v<F_container, typename F_other_view__::F_container>)
            >
            NCPP_FORCE_INLINE TF_view(F_other_view__&& other_view) NCPP_ENABLE_IF_RELEASE(noexcept) :
                container_p_(reinterpret_cast<const F_container*>(other_view.container_p()))
            {

                NCPP_ENABLE_IF_DEBUG(T_increase_owner_counter((F_other_view__&)other_view));

                other_view.reset();

            }
            template<
                class F_other_view__,
                typename = decltype(T_is_same_viewable_container_v<F_container, typename F_other_view__::F_container>)
            >
            NCPP_FORCE_INLINE TF_view& operator = (F_other_view__&& other_view) NCPP_ENABLE_IF_RELEASE(noexcept) {

                container_p_ = reinterpret_cast<const F_container*>(other_view.container_p());

                NCPP_ENABLE_IF_DEBUG(T_increase_owner_counter((F_other_view__&)other_view));

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



        public:
            template<
                typename F_arg__,
                typename F_default_return__ = std::remove_const_t<
                    std::remove_reference_t<
                        decltype((*container_p_)[std::declval<std::remove_const_t<F_arg__>>()])
                    >
                >
            >
            NCPP_FORCE_INLINE utilities::TF_nth_template_arg<
                sizeof(F_default_return__) <= sizeof(void*),
                const F_default_return__&,
                F_default_return__
            > operator[](std::remove_const_t<F_arg__> arg) const {

                return (*container_p_)[arg];
            }



        public:
            template<typename F_arg__, std::enable_if_t<!NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator + (const F_this& a, F_arg__& arg)
            -> decltype(
                std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container&,
                        const std::remove_const_t<F_arg__>&
                    >
                >()
                + std::declval<const std::remove_const_t<F_arg__>&>()
            )
            {

                return *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_) + arg;
            }
            template<typename F_arg__, std::enable_if_t<!NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator + (F_arg__& arg, const F_this& a)
            -> decltype(
                std::declval<const std::remove_const_t<F_arg__>&>()
                + std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container&,
                        const std::remove_const_t<F_arg__>&
                    >
                >()
            )
            {

                return arg + *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_);
            }
            template<typename F_arg__, std::enable_if_t<NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator + (F_arg__& arg, const F_this& a)
            -> decltype(
                std::declval<const typename std::remove_const_t<F_arg__>::F_container&>()
                + std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<typename std::remove_const_t<F_arg__>::F_container, F_container>,
                        const F_container&,
                        const typename std::remove_const_t<F_arg__>::F_container&
                    >
                >()
            )
            {

                return arg.container() + *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_);
            }



        public:
            template<typename F_arg__, std::enable_if_t<!NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator - (const F_this& a, F_arg__& arg)
            -> decltype(
                std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container&,
                        const std::remove_const_t<F_arg__>&
                    >
                >()
                - std::declval<const std::remove_const_t<F_arg__>&>()
            )
            {

                return *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_) - arg;
            }
            template<typename F_arg__, std::enable_if_t<!NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator - (F_arg__& arg, const F_this& a)
            -> decltype(
                std::declval<const std::remove_const_t<F_arg__>&>()
                - std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container&,
                        const std::remove_const_t<F_arg__>&
                    >
                >()
            )
            {

                return arg - *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_);
            }
            template<typename F_arg__, std::enable_if_t<NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator - (F_arg__& arg, const F_this& a)
            -> decltype(
                std::declval<const typename std::remove_const_t<F_arg__>::F_container&>()
                - std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<typename std::remove_const_t<F_arg__>::F_container, F_container>,
                        const F_container&,
                        const typename std::remove_const_t<F_arg__>::F_container&
                    >
                >()
            )
            {

                return arg.container() - *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_);
            }



        public:
            template<typename F_arg__, std::enable_if_t<!NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator == (const F_this& a, F_arg__& arg)
            -> decltype(
                std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container&,
                        const std::remove_const_t<F_arg__>&
                    >
                >()
                == std::declval<const std::remove_const_t<F_arg__>&>()
            )
            {

                return *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_) == arg;
            }
            template<typename F_arg__, std::enable_if_t<!NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator == (F_arg__& arg, const F_this& a)
            -> decltype(
                std::declval<const std::remove_const_t<F_arg__>&>()
                == std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container&,
                        const std::remove_const_t<F_arg__>&
                    >
                >()
            )
            {

                return arg == *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_);
            }
            template<typename F_arg__, std::enable_if_t<NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator == (F_arg__& arg, const F_this& a)
            -> decltype(
                std::declval<const typename std::remove_const_t<F_arg__>::F_container&>()
                == std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<typename std::remove_const_t<F_arg__>::F_container, F_container>,
                        const F_container&,
                        const typename std::remove_const_t<F_arg__>::F_container&
                    >
                >()
            )
            {

                return arg.container() == *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_);
            }



        public:
            template<typename F_arg__, std::enable_if_t<!NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator != (const F_this& a, F_arg__& arg)
            -> decltype(
                std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container&,
                        const std::remove_const_t<F_arg__>&
                    >
                >()
                != std::declval<const std::remove_const_t<F_arg__>&>()
            )
            {

                return *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_) != arg;
            }
            template<typename F_arg__, std::enable_if_t<!NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator != (F_arg__& arg, const F_this& a)
            -> decltype(
                std::declval<const std::remove_const_t<F_arg__>&>()
                != std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container&,
                        const std::remove_const_t<F_arg__>&
                    >
                >()
            )
            {

                return arg != *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_);
            }
            template<typename F_arg__, std::enable_if_t<NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator != (F_arg__& arg, const F_this& a)
            -> decltype(
                std::declval<const typename std::remove_const_t<F_arg__>::F_container&>()
                != std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<typename std::remove_const_t<F_arg__>::F_container, F_container>,
                        const F_container&,
                        const typename std::remove_const_t<F_arg__>::F_container&
                    >
                >()
            )
            {

                return arg.container() != *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_);
            }



        public:
            template<typename F_arg__, std::enable_if_t<!NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator << (const F_this& a, std::remove_const_t<F_arg__>& arg)
            -> decltype(
                std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container&,
                        const std::remove_const_t<F_arg__>&
                    >
                >()
                << std::declval<const std::remove_const_t<F_arg__>&>()
            )
            {

                return *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_) << arg;
            }
            template<typename F_arg__, std::enable_if_t<!NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator << (std::remove_const_t<F_arg__>& arg, const F_this& a)
            -> decltype(
                std::declval<const std::remove_const_t<F_arg__>&>()
                << std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container&,
                        const std::remove_const_t<F_arg__>&
                    >
                >()
            )
            {

                return arg << *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_);
            }
            template<typename F_arg__, std::enable_if_t<NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator << (F_arg__& arg, const F_this& a)
            -> decltype(
                std::declval<const typename std::remove_const_t<F_arg__>::F_container&>()
                << std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<typename std::remove_const_t<F_arg__>::F_container, F_container>,
                        const F_container&,
                        const typename std::remove_const_t<F_arg__>::F_container&
                    >
                >()
            )
            {

                return arg.container() << *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_);
            }



        public:
            template<typename F_arg__, std::enable_if_t<!NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator >> (const F_this& a, F_arg__& arg)
            -> decltype(
                std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container&,
                        const std::remove_const_t<F_arg__>&
                    >
                >()
                >> std::declval<const std::remove_const_t<F_arg__>&>()
            )
            {

                return *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_) >> arg;
            }
            template<typename F_arg__, std::enable_if_t<!NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator >> (F_arg__& arg, const F_this& a)
            -> decltype(
                std::declval<const std::remove_const_t<F_arg__>&>()
                >> std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container&,
                        const std::remove_const_t<F_arg__>&
                    >
                >()
            )
            {

                return arg >> *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_);
            }
            template<typename F_arg__, std::enable_if_t<NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator >> (F_arg__& arg, const F_this& a)
            -> decltype(
                std::declval<const typename std::remove_const_t<F_arg__>::F_container&>()
                >> std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<typename std::remove_const_t<F_arg__>::F_container, F_container>,
                        const F_container&,
                        const typename std::remove_const_t<F_arg__>::F_container&
                    >
                >()
            )
            {

                return arg.container() >> *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_);
            }



        public:
            template<typename F_arg__, std::enable_if_t<!NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator % (const F_this& a, F_arg__& arg)
            -> decltype(
                std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container&,
                        const std::remove_const_t<F_arg__>&
                    >
                >()
                % std::declval<const std::remove_const_t<F_arg__>&>()
            )
            {

                return *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_) % arg;
            }
            template<typename F_arg__, std::enable_if_t<!NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator % (F_arg__& arg, const F_this& a)
            -> decltype(
                std::declval<const std::remove_const_t<F_arg__>&>()
                % std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container&,
                        const std::remove_const_t<F_arg__>&
                    >
                >()
            )
            {

                return arg % *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_);
            }
            template<typename F_arg__, std::enable_if_t<NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator % (F_arg__& arg, const F_this& a)
            -> decltype(
                std::declval<const typename std::remove_const_t<F_arg__>::F_container&>()
                % std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<typename std::remove_const_t<F_arg__>::F_container, F_container>,
                        const F_container&,
                        const typename std::remove_const_t<F_arg__>::F_container&
                    >
                >()
            )
            {

                return arg.container() % *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_);
            }



        public:
            template<typename F_arg__, std::enable_if_t<!NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator * (const F_this& a, F_arg__& arg)
            -> decltype(
                std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container&,
                        const std::remove_const_t<F_arg__>&
                    >
                >()
                * std::declval<const std::remove_const_t<F_arg__>&>()
            )
            {

                return *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_) * arg;
            }
            template<typename F_arg__, std::enable_if_t<!NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator * (F_arg__& arg, const F_this& a)
            -> decltype(
                std::declval<const std::remove_const_t<F_arg__>&>()
                * std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container&,
                        const std::remove_const_t<F_arg__>&
                    >
                >()
            )
            {

                return arg * *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_);
            }
            template<typename F_arg__, std::enable_if_t<NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator * (F_arg__& arg, const F_this& a)
            -> decltype(
                std::declval<const typename std::remove_const_t<F_arg__>::F_container&>()
                * std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<typename std::remove_const_t<F_arg__>::F_container, F_container>,
                        const F_container&,
                        const typename std::remove_const_t<F_arg__>::F_container&
                    >
                >()
            )
            {

                return arg.container() * *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_);
            }



        public:
            template<typename F_arg__, std::enable_if_t<!NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator / (const F_this& a, F_arg__& arg)
            -> decltype(
                std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container&,
                        const std::remove_const_t<F_arg__>&
                    >
                >()
                / std::declval<const std::remove_const_t<F_arg__>&>()
            )
            {

                return *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_) / arg;
            }
            template<typename F_arg__, std::enable_if_t<!NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator / (F_arg__& arg, const F_this& a)
            -> decltype(
                std::declval<const std::remove_const_t<F_arg__>&>()
                / std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container&,
                        const std::remove_const_t<F_arg__>&
                    >
                >()
            )
            {

                return arg / *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_);
            }
            template<typename F_arg__, std::enable_if_t<NCPP_RTTI_IS_HAS_FLAG(std::remove_const_t<F_arg__>, F_view_flag), i32> = 0>
            friend NCPP_FORCE_INLINE auto operator / (F_arg__& arg, const F_this& a)
            -> decltype(
                std::declval<const typename std::remove_const_t<F_arg__>::F_container&>()
                / std::declval<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<typename std::remove_const_t<F_arg__>::F_container, F_container>,
                        const F_container&,
                        const typename std::remove_const_t<F_arg__>::F_container&
                    >
                >()
            )
            {

                return arg.container() / *reinterpret_cast<
                    utilities::TF_nth_template_arg<
                        T_is_same_viewable_container_v<std::remove_const_t<F_arg__>, F_container>,
                        const F_container*,
                        const std::remove_const_t<F_arg__>*
                    >
                >(a.container_p_);
            }



        private:
            template<typename F__, std::enable_if_t<utilities::T_is_has_begin_const<F__>, i32> = 0>
            NCPP_FORCE_INLINE auto T_begin_internal() const {

                return container_p_->begin();
            }
            template<typename F__, std::enable_if_t<!utilities::T_is_has_begin_const<F__>, i32> = 0>
            NCPP_FORCE_INLINE void T_begin_internal() const {

            }
            template<typename F__, std::enable_if_t<utilities::T_is_has_cbegin<F__>, i32> = 0>
            NCPP_FORCE_INLINE auto T_cbegin_internal() const {

                return container_p_->cbegin();
            }
            template<typename F__, std::enable_if_t<!utilities::T_is_has_cbegin<F__>, i32> = 0>
            NCPP_FORCE_INLINE void T_cbegin_internal() const {

            }
            template<typename F__, std::enable_if_t<utilities::T_is_has_end_const<F__>, i32> = 0>
            NCPP_FORCE_INLINE auto T_end_internal() const {

                return container_p_->end();
            }
            template<typename F__, std::enable_if_t<!utilities::T_is_has_end_const<F__>, i32> = 0>
            NCPP_FORCE_INLINE void T_end_internal() const {

            }
            template<typename F__, std::enable_if_t<utilities::T_is_has_cend<F__>, i32> = 0>
            NCPP_FORCE_INLINE auto T_cend_internal() const {

                return container_p_->cend();
            }
            template<typename F__, std::enable_if_t<!utilities::T_is_has_cend<F__>, i32> = 0>
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
#ifdef NCPP_DEBUG
            template<class F_other_view__>
            NCPP_FORCE_INLINE void T_increase_owner_counter(F_other_view__& other_view) {

                if(other_view.owner_counter_p()) {

                    owner_counter_p_ = other_view.owner_counter_p();

                    assert(
                        ([&]()->b8{ owner_counter_p_->fetch_add(1, eastl::memory_order_acq_rel); return true;})()
                        && "the current view is in container-owned mode, all references to the owned container have to be unreferenced before the root owner is destroyed or reset"
                    );

                }

            }
            NCPP_FORCE_INLINE void decrease_owner_counter() {

                if(owner_counter_p_) {

                    u64 prev_owner_counter;

                    assert(
                        ([&]()->b8{ prev_owner_counter = owner_counter_p_->fetch_sub(1, eastl::memory_order_acq_rel); return true;})()
                        && "the current view is in container-owned mode, all references to the owned container have to be unreferenced before the root owner is destroyed or reset"
                    );

                    if(is_root_owner_) {

                        assert((prev_owner_counter == 1) && "the current view is in container-owned mode, all references to the owned container have to be unreferenced before the root owner is destroyed or reset");

                        delete owner_counter_p_;

                    }

                }

            }
#endif

            NCPP_FORCE_INLINE void reset() NCPP_ENABLE_IF_RELEASE(noexcept) {

                NCPP_ENABLE_IF_DEBUG(decrease_owner_counter());

                container_p_ = 0;
            }



        public:
            template<typename F_ostream__>
            friend NCPP_FORCE_INLINE F_ostream__& operator << (F_ostream__& os, const TF_view& view) {

                return (os << (*view.container_p_));
            }

        };



        template<typename F_container__>
        NCPP_FORCE_INLINE TF_view<F_container__> T_to_view(const F_container__& container) noexcept {

            return container;
        }
       
    }

}