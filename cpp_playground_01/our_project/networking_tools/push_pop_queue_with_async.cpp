#include <exception>
#include <future>
#include <iostream>
#include <queue>
#include <thread>
#include <vector>

namespace our_project {
namespace networking_tools {

int push_pop_queue_with_async(const int&& number_of_producers) {
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

  auto q_pop_lambda = [&q, &q_mtx, &q_pop_count, &q_pop_count_mtx]() -> void {
    while (!q.empty()) {
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

  auto future_pool = vector<future<void>>{};
  auto num_base = 64;
  for (auto i = 0; i < number_of_producers; i++) {
    auto name = "producer_thread " + to_string(i);
    auto val = num_base * (i + 1);
    future_pool.push_back(async(q_push_lambda, name, val));
  }

  for (auto&& one_future : future_pool) {
    one_future.get();  // no result but block till the end of exceution

    cout << "future is returned" << endl;
  }

  auto q_pop_future = async(q_pop_lambda);
  q_pop_future.get();  // no result but block till the end of exceution

  return q_pop_count;
}

}  // namespace networking_tools
}  // namespace our_project