#include <our_project/tools/tools.h>

#include <exception>
#include <future>
#include <iostream>
#include <queue>
#include <thread>

#include "our_project/networking_tools/networking_tools.hpp"

int main() {
  {
    using namespace our_project::tools;
    print_hello();
  }

  {
    using namespace std;
    cout << "jthread " << this_thread::get_id() << endl;

    jthread t1 = jthread{[]() -> void {
      cout << "inside the thread" << endl;
      cout << this_thread::get_id() << endl;
    }};

    // this_thread::sleep_for(chrono::seconds{1});
    t1.join();

    cout << "end of block" << endl;
  }

  {
    using namespace std;
    cout << "----- -----" << endl;
    cout << "start of block push_pop_queue_with_jthread" << endl;

    auto q_pop_count =
        our_project::networking_tools::push_pop_queue_with_jthread(4);

    cout << "number of q pop = " << q_pop_count << endl;
    cout << "end of block" << endl;
    cout << "----- -----" << endl;
  }

  {
    using namespace std;
    cout << "----- -----" << endl;
    cout << "start of block" << endl;

    auto divide_lambda = [](int a, int b, promise<int>& result) {
      if (b == 0) {
        auto ex = runtime_error("division by zero");
        result.set_exception(make_exception_ptr(ex));
        return;
      }

      result.set_value(a / b);
    };

    auto p = promise<int>{};
    auto t1 = thread{
        divide_lambda,
        24,
        0,
        ref(p),
    };
    t1.detach();

    auto f = p.get_future();

    try {
      auto value = f.get();
      cout << "value from future = " << value << endl;
    } catch (exception& ex) {
      cout << "exception from future = " << ex.what() << endl;
    }

    cout << "end of block" << endl;
    cout << "----- -----" << endl;
  }

  {
    using namespace std;
    cout << "----- -----" << endl;
    cout << "start of block push_pop_queue_with_async" << endl;
    int i{28};
    decltype(i) j{34};

    cout << j << endl;

    auto q_pop_count =
        our_project::networking_tools::push_pop_queue_with_async(4);

    cout << "number of q pop = " << q_pop_count << endl;
    cout << "end of block" << endl;
    cout << "----- -----" << endl;
  }

  {
    using namespace std;
    cout << "----- -----" << endl;
    cout << "start of block push_pop_queue_with_latch" << endl;

    auto q_pop_count =
        our_project::networking_tools::push_pop_queue_with_latch(5);

    cout << "number of q pop = " << q_pop_count << endl;
    cout << "end of block" << endl;
    cout << "----- -----" << endl;
  }

  return 0;
}
