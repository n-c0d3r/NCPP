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
#include <ncpp/utilities/nth_template_targ.hpp>
#include <ncpp/utilities/template_targ_list.hpp>
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
        class TF_large_view;

    }

}



NCPP_CONTAINERS_DEFINE_ALLOCATOR_BINDING(
    NCPP_MA(ncpp::containers::TF_large_view<F_container__>),
    NCPP_MA(ncpp::containers::TF_container_allocator<F_container__>),
    NCPP_MA(ncpp::containers::TF_large_view<ncpp::containers::TF_bind_container_allocator<F_container__, F_new_allocator__>>),
    typename F_container__
);



namespace ncpp {

	namespace containers {

        namespace internal {

            struct F_large_view_flag {};



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

        template<typename F_container__, typename F_another__>
        using TF_try_march_container_allocator = typename internal::TF_try_march_container_allocator<
            F_container__,
            std::remove_const_t<std::remove_reference_t<F_another__>>,
            !std::is_same_v<containers::TF_container_allocator<std::remove_const_t<std::remove_reference_t<F_another__>>>, void>
        >::F;



        template<typename F1__, typename F2__>
        concept T_is_same_viewable_container = (
            T_is_same_container<F1__, F2__>
            && (utilities::T_sizeof<TF_container_allocator<F1__>> == utilities::T_sizeof<TF_container_allocator<F2__>>)
        );



        template<typename F__>
        concept T_is_large_view = requires {

            typename std::remove_const_t<std::remove_reference_t<F__>>::F_large_view_flag;

        };
        template<typename F__>
        concept T_not_large_view = !T_is_large_view<F__>;



        template<typename F1__, typename F2__>
        concept T_is_same_large_views = requires {

            typename F1__::F_container;
            typename F2__::F_container;

            {
                T_is_same_viewable_container<
                    typename F1__::F_container,
                    typename F2__::F_container
                >
            };

        };



#ifdef NCPP_DEBUG
        struct F_large_view_owner_counter {

            au64 m = 1;

            ~F_large_view_owner_counter(){

                assert((m.load(eastl::memory_order_acquire) == 0) && "all larges to the owned container have to be unlarged before the view owner counter is destroyed");

            }

        };
#endif



        template<typename F_container__>
        class TF_large_view {

        public:
            using F_this = TF_large_view<F_container__>;
            using F_container = F_container__;
            using F_allocator = TF_container_allocator<F_container__>;

            using F_large_view_flag = containers::internal::F_large_view_flag;



        private:
            const F_container* container_p_ = 0;

#ifdef NCPP_DEBUG
            F_large_view_owner_counter* owner_counter_p_ = 0;
#endif

        public:
            NCPP_FORCE_INLINE const F_container* container_p() const { return container_p_; }
            NCPP_FORCE_INLINE const F_container& container() const { return *container_p_; }

            NCPP_FORCE_INLINE b8 is_null() const { return (container_p_ == 0); }
            NCPP_FORCE_INLINE b8 is_valid() const { return (container_p_ != 0); }

#ifdef NCPP_DEBUG
            NCPP_FORCE_INLINE F_large_view_owner_counter* owner_counter_p() const {

                return (F_large_view_owner_counter*)owner_counter_p_;
            }
#endif



        public:
            NCPP_FORCE_INLINE TF_large_view() = default;

            NCPP_FORCE_INLINE ~TF_large_view() NCPP_ENABLE_IF_RELEASE(noexcept) {

                reset();

            }



        public:
            template<
                typename F__,
                std::enable_if_t<!T_is_same_viewable_container<F_container, F__>, i32> = 0
            >
            NCPP_FORCE_INLINE TF_large_view(
                const F__& x,
                const utilities::TF_no_constructor<F_container>& container = utilities::TF_no_constructor<F_container>{}
                NCPP_ENABLE_IF_DEBUG(, const F_large_view_owner_counter& owner_counter = F_large_view_owner_counter())
            ) :
                container_p_((const F_container*)&container)

#ifdef NCPP_DEBUG
                ,
                owner_counter_p_((F_large_view_owner_counter*)(&owner_counter))
#endif
            {

                new ((F_container*)&container) F_container(x);

            }
            template<typename F_fake_container__ = F_container, std::enable_if_t<!std::is_same_v<void, utilities::TF_value<F_fake_container__>>, i32> = 0>
            NCPP_FORCE_INLINE TF_large_view(
                std::initializer_list<utilities::TF_value<F_container>> x, 
                const utilities::TF_no_constructor<F_container>& container = utilities::TF_no_constructor<F_container>{}
                NCPP_ENABLE_IF_DEBUG(, const F_large_view_owner_counter& owner_counter = F_large_view_owner_counter())
            ) :
                container_p_((const F_container*)&container)

#ifdef NCPP_DEBUG
                ,
                owner_counter_p_((F_large_view_owner_counter*)(&owner_counter))
#endif
            {

                new ((F_container*)&container) F_container(x);

            }



        public:
            template<
                typename F_other_container__,
                std::enable_if_t<T_is_same_viewable_container<F_container, F_other_container__>, i32> = 0
            >
            NCPP_FORCE_INLINE operator const F_other_container__&() const noexcept {

                return *reinterpret_cast<const F_other_container__*>(container_p_);
            }



        public:
            NCPP_FORCE_INLINE TF_large_view(const F_container& other_container) noexcept :
                container_p_(reinterpret_cast<const F_container*>(&other_container))
            {



            }
            NCPP_FORCE_INLINE TF_large_view& operator = (const F_container& other_container) noexcept
            {

                container_p_ = reinterpret_cast<const F_container*>(&other_container);

                return *this;
            }



        public:
            NCPP_FORCE_INLINE TF_large_view(const F_this& other_view) NCPP_ENABLE_IF_RELEASE(noexcept) :
                container_p_(reinterpret_cast<const F_container*>(other_view.container_p()))
            {

                NCPP_ENABLE_IF_DEBUG(T_increase_owner_counter((F_this&)other_view));

            }
            NCPP_FORCE_INLINE TF_large_view& operator = (const F_this& other_view) NCPP_ENABLE_IF_RELEASE(noexcept) {

                container_p_ = reinterpret_cast<const F_container*>(other_view.container_p());

                NCPP_ENABLE_IF_DEBUG(T_increase_owner_counter((F_this&)other_view));

                return *this;
            }



        public:
            NCPP_FORCE_INLINE TF_large_view(F_this&& other_view) NCPP_ENABLE_IF_RELEASE(noexcept) :
                container_p_(reinterpret_cast<const F_container*>(other_view.container_p()))
            {

                NCPP_ENABLE_IF_DEBUG(T_increase_owner_counter((F_this&)other_view));

                other_view.reset();

            }
            NCPP_FORCE_INLINE TF_large_view& operator = (F_this&& other_view) NCPP_ENABLE_IF_RELEASE(noexcept) {

                container_p_ = reinterpret_cast<const F_container*>(other_view.container_p());

                NCPP_ENABLE_IF_DEBUG(T_increase_owner_counter((F_this&)other_view));

                other_view.reset();

                return *this;
            }



        public:
            template<
                typename F_other_container__,
                std::enable_if_t<T_is_same_viewable_container<F_container, F_other_container__>, i32> = 0
            >
            NCPP_FORCE_INLINE TF_large_view(const F_other_container__& other_container) noexcept :
                container_p_(reinterpret_cast<const F_container*>(&other_container))
            {



            }
            template<
                typename F_other_container__,
                std::enable_if_t<T_is_same_viewable_container<F_container, F_other_container__>, i32> = 0
            >
            NCPP_FORCE_INLINE TF_large_view& operator = (const F_other_container__& other_container) noexcept
            {

                container_p_ = reinterpret_cast<const F_container*>(&other_container);

                return *this;
            }



        public:
            template<
                class F_other_view__,
                std::enable_if_t<T_is_same_large_views<F_this, F_other_view__>, i32> = 0
            >
            NCPP_FORCE_INLINE TF_large_view(const F_other_view__& other_view) NCPP_ENABLE_IF_RELEASE(noexcept) :
                container_p_(reinterpret_cast<const F_container*>(other_view.container_p()))
            {

                NCPP_ENABLE_IF_DEBUG(T_increase_owner_counter((F_other_view__&)other_view));

            }
            template<
                class F_other_view__,
                std::enable_if_t<T_is_same_large_views<F_this, F_other_view__>, i32> = 0
            >
            NCPP_FORCE_INLINE TF_large_view& operator = (const F_other_view__& other_view) NCPP_ENABLE_IF_RELEASE(noexcept) {

                container_p_ = reinterpret_cast<const F_container*>(other_view.container_p());

                NCPP_ENABLE_IF_DEBUG(T_increase_owner_counter((F_other_view__&)other_view));

                return *this;
            }



        public:
            template<
                class F_other_view__,
                std::enable_if_t<T_is_same_large_views<F_this, F_other_view__>, i32> = 0
            >
            NCPP_FORCE_INLINE TF_large_view(F_other_view__&& other_view) NCPP_ENABLE_IF_RELEASE(noexcept) :
                container_p_(reinterpret_cast<const F_container*>(other_view.container_p()))
            {

                NCPP_ENABLE_IF_DEBUG(T_increase_owner_counter((F_other_view__&)other_view));

                other_view.reset();

            }
            template<
                class F_other_view__,
                std::enable_if_t<T_is_same_large_views<F_this, F_other_view__>, i32> = 0
            >
            NCPP_FORCE_INLINE TF_large_view& operator = (F_other_view__&& other_view) NCPP_ENABLE_IF_RELEASE(noexcept) {

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
            NCPP_FORCE_INLINE utilities::TF_nth_template_targ<
                sizeof(F_default_return__) <= sizeof(void*),
                const F_default_return__&,
                F_default_return__
            > operator[](F_arg__ arg) const {

                return (*container_p_)[arg];
            }



#define NCPP_CONTAINERS_DEFINE_VIEW_OPERATORS(Operator) \
            template<T_not_large_view F_arg__>\
            friend NCPP_FORCE_INLINE auto operator Operator (F_arg__&& arg, const F_this& a) \
            ->decltype(                                  \
                (arg Operator std::declval<TF_try_march_container_allocator<F_container__, F_arg__>>())                                             \
            )                                             \
            {\
\
                return (arg Operator ( *((const TF_try_march_container_allocator<F_container__, F_arg__>*)a.container_p_) ));\
            }\
            template<T_not_large_view F_arg__>\
            friend NCPP_FORCE_INLINE auto operator Operator (const F_this& a, F_arg__&& arg) \
            ->decltype(                                  \
                (std::declval<TF_try_march_container_allocator<F_container__, F_arg__>>() Operator arg)                                             \
            )                                             \
            {\
\
                return (arg Operator ( *((const TF_try_march_container_allocator<F_container__, F_arg__>*)a.container_p_) ));\
            }\
            template<T_is_large_view F_arg__>\
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
                    ( *((typename F_arg__::F_container*)arg.container_p()) )                             \
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
            friend NCPP_FORCE_INLINE F_ostream__& operator << (F_ostream__& os, const TF_large_view& view) {

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
                        && "all larges to the owned container have to be unlarged before the view owner counter is destroyed"
                    );

                }

            }
            NCPP_FORCE_INLINE void decrease_owner_counter() {

                if(owner_counter_p_) {

                    assert(
                        ([this]()->b8{ owner_counter_p_->m.fetch_sub(1, eastl::memory_order_acq_rel); return true;})()
                        && "all larges to the owned container have to be unlarged before the view owner counter is destroyed"
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
        NCPP_FORCE_INLINE TF_large_view<F_container__> T_large_view(const F_container__& container) noexcept {

            return container;
        }



        template<typename F__>
        using TF_size_optimized_view = utilities::TF_nth_template_targ<
            (utilities::T_sizeof<F__> > sizeof(void*)),
            F__,
            TF_large_view<F__>
        >;

        template<typename F__>
        NCPP_FORCE_INLINE TF_size_optimized_view<F__> T_size_optimized_view(const F__& container) noexcept {

            return container;
        }



        template<typename F__, bool is_always_mutable__ = false>
        using TF_view = utilities::TF_nth_template_targ<
            is_always_mutable__,
            TF_size_optimized_view<F__>,
            TF_large_view<F__>
        >;

        template<typename F__>
        NCPP_FORCE_INLINE TF_view<F__> T_view(const F__& container) noexcept {

            return container;
        }

    }



    namespace utilities {

        template<typename... F__>
        struct TF_to_template_targ_list<containers::TF_large_view<F__...>> {

            using F = TF_template_targ_list<F__...>;

        };

    }

}