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
#include <ncpp/utilities/no_constructor.hpp>
#include <ncpp/utilities/is_streamable.hpp>
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

        template<typename F_container__>
        class TF_view;

    }

}



NCPP_CONTAINERS_DEFINE_ALLOCATOR_BINDING(
    NCPP_MA(ncpp::containers::TF_view<F_container__>),
    NCPP_MA(ncpp::containers::TF_container_allocator<F_container__>),
    NCPP_MA(ncpp::containers::TF_view<ncpp::containers::TF_bind_container_allocator<F_container__, F_new_allocator__>>),
    typename F_container__
);



namespace ncpp {

	namespace containers {

        namespace internal {

            struct F___ncpp_view_flag___ {};



            template<typename F_container__, typename F_another__, b8 is_another_has_allocator__>
            struct TF_try_march_container_allocator;

            template<typename F_container__, typename F_another__>
            struct TF_try_march_container_allocator<F_container__, F_another__, true> {

                using F = TF_bind_container_allocator<F_container__, containers::TF_container_allocator<F_another__>>;

            };
            template<typename F_container__, typename F_another__>
            struct TF_try_march_container_allocator<F_container__, F_another__, false> {

                using F = F_container__;

            };

        }

        template<typename F_container__, typename F_another__, typename F_cleaned_another__ = std::remove_const_t<std::remove_reference_t<F_another__>>>
        using TF_try_march_container_allocator = typename internal::TF_try_march_container_allocator<
            F_container__,
            F_cleaned_another__,
            !std::is_same_v<containers::TF_container_allocator<F_cleaned_another__>, void>
        >::F;



        template<typename F1__, typename F2__>
        concept T_is_same_viewable_containers = (
                T_is_same_containers<F1__, F2__>
                && (utilities::T_sizeof<TF_container_allocator<F1__>> == utilities::T_sizeof<TF_container_allocator<F2__>>)
        );
        template<typename F1__, typename F2__>
        concept T_not_same_viewable_containers = !T_is_same_viewable_containers<F1__, F2__>;



        template<typename F__>
        concept T_is_view = requires {

            typename std::remove_const_t<std::remove_reference_t<F__>>::F___ncpp_view_flag___;

        };
        template<typename F__>
        concept T_not_view = !T_is_view<F__>;



        template<typename F1__, typename F2__>
        concept T_is_same_views = requires {

            typename F1__::F_container;
            typename F2__::F_container;

            {
                T_is_same_viewable_containers<
                    typename F1__::F_container,
                    typename F2__::F_container
                >
            };

        };



#ifdef NCPP_DEBUG
        struct F_view_owner_counter {

            au64 m = 1;

            ~F_view_owner_counter(){

                assert((m.load(eastl::memory_order_acquire) == 0) && "all references to the owned container have to be unreferenced before the view owner counter is destroyed");

            }

        };
#endif



        template<typename F_container__>
        class TF_view {

        public:
            using F_this = TF_view<F_container__>;
            using F_container = F_container__;
            using F_allocator = TF_container_allocator<F_container__>;

            using F___ncpp_view_flag___ = containers::internal::F___ncpp_view_flag___;



        private:
            const F_container* container_p_ = 0;

#ifdef NCPP_DEBUG
            F_view_owner_counter* owner_counter_p_ = 0;
#endif

        public:
            NCPP_FORCE_INLINE const F_container* container_p() const { return container_p_; }
            NCPP_FORCE_INLINE const F_container& container() const { return *container_p_; }

            NCPP_FORCE_INLINE b8 is_null() const { return (container_p_ == 0); }
            NCPP_FORCE_INLINE b8 is_valid() const { return (container_p_ != 0); }

#ifdef NCPP_DEBUG
            NCPP_FORCE_INLINE F_view_owner_counter* owner_counter_p() const {

                return (F_view_owner_counter*)owner_counter_p_;
            }
#endif



        public:
            NCPP_FORCE_INLINE TF_view() = default;

            NCPP_FORCE_INLINE ~TF_view() NCPP_ENABLE_IF_RELEASE(noexcept) {

                reset();

            }



        public:
            template<
                typename F__
            >
            requires T_not_same_viewable_containers<F_container, F__>
            NCPP_FORCE_INLINE TF_view(
                const F__& x, 
                const utilities::TF_no_constructor<F_container>& container = utilities::TF_no_constructor<F_container>{}
                NCPP_ENABLE_IF_DEBUG(, const F_view_owner_counter& owner_counter = F_view_owner_counter())
            ) :
                container_p_((const F_container*)&container)

#ifdef NCPP_DEBUG
                ,
                owner_counter_p_((F_view_owner_counter*)(&owner_counter))
#endif
            {

                new ((F_container*)&container) F_container(x);

            }
            template<typename F_fake_container__ = F_container>
            requires utilities::T_is_has_key<F_fake_container__>
            NCPP_FORCE_INLINE TF_view(
                std::initializer_list<utilities::TF_key<F_container>> x, 
                const utilities::TF_no_constructor<F_container>& container = utilities::TF_no_constructor<F_container>{}
                NCPP_ENABLE_IF_DEBUG(, const F_view_owner_counter& owner_counter = F_view_owner_counter())
            ) :
                container_p_((const F_container*)&container)

#ifdef NCPP_DEBUG
                ,
                owner_counter_p_((F_view_owner_counter*)(&owner_counter))
#endif
            {

                new ((F_container*)&container) F_container(x);

            }
            template<typename F_fake_container__ = F_container>
            requires utilities::T_is_has_value<F_fake_container__>
            NCPP_FORCE_INLINE TF_view(
                std::initializer_list<utilities::TF_value<F_container>> x, 
                const utilities::TF_no_constructor<F_container>& container = utilities::TF_no_constructor<F_container>{}
                NCPP_ENABLE_IF_DEBUG(, const F_view_owner_counter& owner_counter = F_view_owner_counter())
            ) :
                container_p_((const F_container*)&container)

#ifdef NCPP_DEBUG
                ,
                owner_counter_p_((F_view_owner_counter*)(&owner_counter))
#endif
            {

                new ((F_container*)&container) F_container(x);

            }
            template<typename F_fake_container__ = F_container>
            requires utilities::T_is_has_node<F_fake_container__>
            NCPP_FORCE_INLINE TF_view(
                std::initializer_list<utilities::TF_node<F_container>> x, 
                const utilities::TF_no_constructor<F_container>& container = utilities::TF_no_constructor<F_container>{}
                NCPP_ENABLE_IF_DEBUG(, const F_view_owner_counter& owner_counter = F_view_owner_counter())
            ) :
                container_p_((const F_container*)&container)

#ifdef NCPP_DEBUG
                ,
                owner_counter_p_((F_view_owner_counter*)(&owner_counter))
#endif
            {

                new ((F_container*)&container) F_container(x);

            }
            template<typename F_fake_container__ = F_container>
            requires utilities::T_is_has_item<F_fake_container__>
            NCPP_FORCE_INLINE TF_view(
                std::initializer_list<utilities::TF_item<F_container>> x, 
                const utilities::TF_no_constructor<F_container>& container = utilities::TF_no_constructor<F_container>{}
                NCPP_ENABLE_IF_DEBUG(, const F_view_owner_counter& owner_counter = F_view_owner_counter())
            ) :
                container_p_((const F_container*)&container)

#ifdef NCPP_DEBUG
                ,
                owner_counter_p_((F_view_owner_counter*)(&owner_counter))
#endif
            {

                new ((F_container*)&container) F_container(x);

            }



        public:
            template<
                typename F_other_container__
            >
            requires T_is_same_viewable_containers<F_container, F_other_container__>
            NCPP_FORCE_INLINE operator const F_other_container__&() const noexcept {

                return *reinterpret_cast<const F_other_container__*>(container_p_);
            }



        public:
            NCPP_FORCE_INLINE TF_view(const F_container& other_container) noexcept :
                container_p_(reinterpret_cast<const F_container*>(&other_container))
            {



            }
            NCPP_FORCE_INLINE TF_view& operator = (const F_container& other_container) noexcept
            {

                container_p_ = reinterpret_cast<const F_container*>(&other_container);

                return *this;
            }



        public:
            NCPP_FORCE_INLINE TF_view(const F_this& other_view) NCPP_ENABLE_IF_RELEASE(noexcept) :
                container_p_(reinterpret_cast<const F_container*>(other_view.container_p()))
            {

                NCPP_ENABLE_IF_DEBUG(T_increase_owner_counter((F_this&)other_view));

            }
            NCPP_FORCE_INLINE TF_view& operator = (const F_this& other_view) NCPP_ENABLE_IF_RELEASE(noexcept) {

                container_p_ = reinterpret_cast<const F_container*>(other_view.container_p());

                NCPP_ENABLE_IF_DEBUG(T_increase_owner_counter((F_this&)other_view));

                return *this;
            }



        public:
            NCPP_FORCE_INLINE TF_view(F_this&& other_view) NCPP_ENABLE_IF_RELEASE(noexcept) :
                container_p_(reinterpret_cast<const F_container*>(other_view.container_p()))
            {

                NCPP_ENABLE_IF_DEBUG(T_increase_owner_counter((F_this&)other_view));

                other_view.reset();

            }
            NCPP_FORCE_INLINE TF_view& operator = (F_this&& other_view) NCPP_ENABLE_IF_RELEASE(noexcept) {

                container_p_ = reinterpret_cast<const F_container*>(other_view.container_p());

                NCPP_ENABLE_IF_DEBUG(T_increase_owner_counter((F_this&)other_view));

                other_view.reset();

                return *this;
            }



        public:
            template<
                typename F_other_container__
            >
            requires T_is_same_viewable_containers<F_container, F_other_container__>
            NCPP_FORCE_INLINE TF_view(const F_other_container__& other_container) noexcept :
                container_p_(reinterpret_cast<const F_container*>(&other_container))
            {



            }
            template<
                typename F_other_container__
            >
            requires T_is_same_viewable_containers<F_container, F_other_container__>
            NCPP_FORCE_INLINE TF_view& operator = (const F_other_container__& other_container) noexcept
            {

                container_p_ = reinterpret_cast<const F_container*>(&other_container);

                return *this;
            }



        public:
            template<
                class F_other_view__
            >
            requires T_is_same_views<F_this, F_other_view__>
            NCPP_FORCE_INLINE TF_view(const F_other_view__& other_view) NCPP_ENABLE_IF_RELEASE(noexcept) :
                container_p_(reinterpret_cast<const F_container*>(other_view.container_p()))
            {

                NCPP_ENABLE_IF_DEBUG(T_increase_owner_counter((F_other_view__&)other_view));

            }
            template<
                class F_other_view__
            >
            requires T_is_same_views<F_this, F_other_view__>
            NCPP_FORCE_INLINE TF_view& operator = (const F_other_view__& other_view) NCPP_ENABLE_IF_RELEASE(noexcept) {

                container_p_ = reinterpret_cast<const F_container*>(other_view.container_p());

                NCPP_ENABLE_IF_DEBUG(T_increase_owner_counter((F_other_view__&)other_view));

                return *this;
            }



        public:
            template<
                class F_other_view__
            >
            requires T_is_same_views<F_this, F_other_view__>
            NCPP_FORCE_INLINE TF_view(F_other_view__&& other_view) NCPP_ENABLE_IF_RELEASE(noexcept) :
                container_p_(reinterpret_cast<const F_container*>(other_view.container_p()))
            {

                NCPP_ENABLE_IF_DEBUG(T_increase_owner_counter((F_other_view__&)other_view));

                other_view.reset();

            }
            template<
                class F_other_view__
            >
            requires T_is_same_views<F_this, F_other_view__>
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
                        decltype((*container_p_)[std::declval<std::remove_reference_t<std::remove_const_t<F_arg__>>>()])
                    >
                >
            >
            NCPP_FORCE_INLINE utilities::TF_nth_template_arg<
                sizeof(F_default_return__) <= sizeof(void*),
                const F_default_return__&,
                F_default_return__
            > operator[](F_arg__ arg) const {

                return (*container_p_)[arg];
            }



#define NCPP_CONTAINERS_DEFINE_VIEW_OPERATORS(Operator) \
            template<T_not_view F_arg__>\
            friend NCPP_FORCE_INLINE auto operator Operator (F_arg__&& arg, const F_this& a) \
            ->decltype(                                  \
                (arg Operator std::declval<TF_try_march_container_allocator<F_container__, F_arg__>>())                                             \
            )                                             \
            {\
\
                return (arg Operator ( *((const TF_try_march_container_allocator<F_container__, F_arg__>*)a.container_p_) ));\
            }\
            template<T_not_view F_arg__>\
            friend NCPP_FORCE_INLINE auto operator Operator (const F_this& a, F_arg__&& arg) \
            ->decltype(                                  \
                (std::declval<TF_try_march_container_allocator<F_container__, F_arg__>>() Operator arg)                                             \
            )                                             \
            {\
\
                return (arg Operator ( *((const TF_try_march_container_allocator<F_container__, F_arg__>*)a.container_p_) ));\
            }\
            template<T_is_view F_arg__>\
            friend NCPP_FORCE_INLINE auto operator Operator (const F_this& a, F_arg__&& arg) \
            ->decltype(                                  \
                (                                        \
                    std::declval<typename TF_try_march_container_allocator<F_this, F_arg__>::F_container>()                                            \
                    Operator                                 \
                    std::declval<typename F_arg__::F_container>()                                      \
                )                                             \
            )                                             \
            {\
\
                return (                                 \
                    ( *((const TF_try_march_container_allocator<F_this, F_arg__>*)a.container_p()) )                             \
                    Operator                             \
                    ( *((const TF_try_march_container_allocator<F_arg__, F_this>*)arg.container_p()) )                             \
                );\
            }



        public:
            NCPP_CONTAINERS_DEFINE_VIEW_OPERATORS(<<);
            NCPP_CONTAINERS_DEFINE_VIEW_OPERATORS(>>);
            NCPP_CONTAINERS_DEFINE_VIEW_OPERATORS(+);
            NCPP_CONTAINERS_DEFINE_VIEW_OPERATORS(-);
            NCPP_CONTAINERS_DEFINE_VIEW_OPERATORS(*);
            NCPP_CONTAINERS_DEFINE_VIEW_OPERATORS(/);
            NCPP_CONTAINERS_DEFINE_VIEW_OPERATORS(%);
            NCPP_CONTAINERS_DEFINE_VIEW_OPERATORS(&);
            NCPP_CONTAINERS_DEFINE_VIEW_OPERATORS(==);
            NCPP_CONTAINERS_DEFINE_VIEW_OPERATORS(!=);



        public:
            template<typename F_ostream__>
            friend NCPP_FORCE_INLINE F_ostream__& operator << (F_ostream__& os, const TF_view& view) {

                return (os << (*view.container_p_));
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
                        ([&]()->b8{ owner_counter_p_->m.fetch_add(1, eastl::memory_order_acq_rel); return true;})()
                        && "all references to the owned container have to be unreferenced before the view owner counter is destroyed"
                    );

                }

            }
            NCPP_FORCE_INLINE void decrease_owner_counter() {

                if(owner_counter_p_) {

                    assert(
                        ([this]()->b8{ owner_counter_p_->m.fetch_sub(1, eastl::memory_order_acq_rel); return true;})()
                        && "all references to the owned container have to be unreferenced before the view owner counter is destroyed"
                    );

                }

            }
#endif

            NCPP_FORCE_INLINE void reset() NCPP_ENABLE_IF_RELEASE(noexcept) {

                NCPP_ENABLE_IF_DEBUG(decrease_owner_counter());

                container_p_ = 0;
            }

        };



        template<typename F_container__>
        NCPP_FORCE_INLINE TF_view<F_container__> T_to_view(const F_container__& container) noexcept {

            return container;
        }
       
    }

}