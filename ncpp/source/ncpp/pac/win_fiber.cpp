#include <ncpp/.hpp>



namespace ncpp {

	namespace pac {

#ifdef NCPP_WINDOWS_PLATFORM
		win_fiber::win_fiber(fiber_creation_mode mode, functor_type&& functor) :
			creation_mode_(mode),
			platform_fiber_(0),
			functor_(std::move(functor))
		{

			switch (creation_mode_)
			{
			case ncpp::pac::fiber_creation_mode::CONVERT_FROM_THREAD:
				platform_fiber_ = ConvertThreadToFiber(0);
				break;
			case ncpp::pac::fiber_creation_mode::NEW:
				platform_fiber_ = CreateFiber(0, proc, this);
				break;
			default:
				break;
			}

		}
		win_fiber::~win_fiber() {

			if (creation_mode_ == fiber_creation_mode::NEW)
				DeleteFiber(platform_fiber_);
			else
				ConvertFiberToThread();

		}



		void win_fiber::switch_to_this() {

			SwitchToFiber(platform_fiber_);

		}
#endif

	}

}