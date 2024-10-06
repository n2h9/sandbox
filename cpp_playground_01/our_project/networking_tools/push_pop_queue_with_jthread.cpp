#include <exception>
#include <future>
#include <iostream>
#include <queue>
#include <thread>
#include <vector>

namespace our_project {
namespace networking_tools {

int push_pop_queue_with_jthread(const int&& number_of_producers) {
  using namespace std;

  auto q = std::queue<int>{};
  auto q_mtx = mutex{};

  auto q_push_lambda = [&q, &q_mtx](auto name, auto base) -> void {
    for (auto i : {1, 2, 4, 5, 7, 8}) {
      auto val = base + i;
      cout << name << ": push " << val << " to q" << endl;
      q_mtx.lock();
      q.push(val);
      q_mtx.unlock();
    }
  };

  auto q_pop_count = 0;
  auto q_pop_count_mtx = mutex{};

  auto q_pop_lambda = [&q, &q_mtx, &q_pop_count,
                       &q_pop_count_mtx](stop_token st) -> void {
    while (!st.stop_requested() || !q.empty()) {
      if (q.empty()) {
        continue;
      }
      q_mtx.lock();
      auto val = q.front();
      q.pop();
      q_mtx.unlock();

      cout << val << endl;

      q_pop_count_mtx.lock();
      ++q_pop_count;
      q_pop_count_mtx.unlock();
    }
  };

  jthread pop_thread{q_pop_lambda};

  auto thread_pool = vector<thread*>{};
  auto num_base = 64;
  for (auto i = 0; i < number_of_producers; i++) {
    auto name = "producer_thread " + to_string(i);
    auto val = num_base * (i + 1);
    thread_pool.push_back(new thread{q_push_lambda, name, val});
  }

  for (auto&& t : thread_pool) {
    t->join();
    delete t;
    cout << "thread is joined" << endl;
  }

  pop_thread.request_stop();
  pop_thread.join();

  return q_pop_count;
}

}  // namespace networking_tools
}  // namespace our_project