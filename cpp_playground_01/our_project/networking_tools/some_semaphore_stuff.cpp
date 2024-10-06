#include <iostream>
#include <semaphore>
#include <thread>
#include <vector>

namespace our_project {
namespace networking_tools {

void some_semaphore_stuff() {
  using namespace std;

  cout << "here am I" << endl;

  const auto num_of_workers = 4;

  auto sem = counting_semaphore<num_of_workers>{num_of_workers};

  auto work_lambda = [&sem](auto worker_name) -> void {
    // number of iteration each threadh to perform
    const auto counter = 4;

    for (auto i = 0; i < counter; i++) {
      sem.acquire();
      cout << "worker " << worker_name << " is working now (iteration = " << i
           << ") . . . " << endl;
      this_thread::sleep_for(2s);
      cout << "worker " << worker_name
           << " finished its work (iteration = " << i << ")" << endl;
      sem.release();
      // sleep here, so to increase chances other thread to pick up the work :)
      this_thread::sleep_for(1s);
    }
  };

  const auto num_of_threads = 32;

  auto thread_pool = vector<thread*>{};
  for (auto i = 0; i < num_of_threads; i++) {
    auto name = "worker " + to_string(i);
    thread_pool.push_back(new thread{work_lambda, name});
  }

  for (auto&& one_thread : thread_pool) {
    one_thread->join();
    delete one_thread;
  }

  cout << "all done" << endl;
}

}  // namespace networking_tools
}  // namespace our_project