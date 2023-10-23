
#include <ncpp/.hpp>

using namespace ncpp;



class F_event_1 : public event::F_event {



};

class F_event_2 : public event::F_event {



};



class F_sample_event_storage : public event::F_event_storage {

public:
	F_sample_event_storage() {

		NCPP_ADD_STATIC_EVENTS();

	}
	~F_sample_event_storage() {



	}



public:
	F_event_1 e1;
	F_event_2 e2;

	NCPP_DECLARE_STATIC_EVENTS(
		e1, 
		e2
	);

};
 


int main() {

	{

		F_sample_event_storage event_storage;

		event::F_event& e_r = event_storage.T_get_event<F_event_1>();

		auto listener_handle1 = e_r.T_push_back_listener([](auto& e) {

			std::cout << "Hello Event 1" << std::endl;

		});

		auto listener_handle2 = e_r.T_push_front_listener([](auto& e) {

			std::cout << "Hello Event 2" << std::endl;

		});

		e_r.invoke();

		e_r.remove_listener(listener_handle1);

		e_r.invoke();

	}

	mem::log_memory_stats();

	pause_console();

	return 0;
}
