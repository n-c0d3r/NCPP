#pragma once

#include <ncpp/prerequisites.hpp>
#include <ncpp/object.hpp>



namespace ncpp {

	template<
	    typename F_object_allocator__ = mem::F_object_allocator,
		class F_object_options__ = F_default_object_options
	>
	struct TF_garbage_collection_options {

	public:
		using F_object_allocator = F_object_allocator__;
		using F_object_options = F_object_options__;

	public:
		template<typename F_passed_object__, typename F_requirements__ = F_no_requirements>
		using TK = ncpp::TK<
			F_passed_object__,
			F_object_options,
			true,
			F_requirements__
		>;
		template<typename F_passed_object__, typename F_requirements__ = F_no_requirements>
		using TU = ncpp::TU<
			F_passed_object__,
			F_object_allocator,
			F_object_options,
			true,
			F_requirements__
		>;

	};

	using F_default_garbage_collection_options = TF_garbage_collection_options<>;



	template<class F_garbage_collection_options__>
	class TA_garbage_collectable {

	public:
		using F_garbage_collection_options = F_garbage_collection_options__;



	private:
		u64 last_gc_sweep_frame_ = NCPP_U64_MAX;

	public:
		NCPP_FORCE_INLINE u64 last_gc_sweep_frame() const noexcept { return last_gc_sweep_frame_; }



	protected:
		TA_garbage_collectable() = default;

	public:
		virtual ~TA_garbage_collectable() = default;



	public:
		virtual void gc_sweep(u64 frame) {

			last_gc_sweep_frame_ = frame;
		}
		virtual void gc_collect() {
		}

	};



	template<class F_passed_object__, class F_garbage_collection_options__ = F_default_garbage_collection_options >
	class TGC {

	private:
		using F_this = TGC<F_passed_object__, F_passed_object__>;

	public:
		using F_passed_object = F_passed_object__;
		using F_object = std::remove_reference_t<F_passed_object>;

		using F_garbage_collection_options = F_garbage_collection_options__;

		using U = typename F_garbage_collection_options::template TU<F_passed_object>;
		using K = typename F_garbage_collection_options::template TK<F_passed_object>;



	private:
		K oref_;

	public:
		NCPP_FORCE_INLINE const auto& oref() const noexcept { return oref_; }



	public:
		TGC() = default;
		~TGC() {
			// before circular referencing happens, there must be 1 GC reference linked to the graph that is destroyed
			// so, only the GC references that is destroyed need to be checked
			enqueue_checking_internal();
		}

	private:
		void enqueue_checking_internal() {
		}

	};

}