#include <exception>
#include <future>
#include <iostream>
#include <queue>
#include <thread>

void push_pop_queue_with_async() {
  using namespace std;
  cout << "----- -----" << endl;
  cout << "start of block push_pop_queue_with_async" << endl;

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

  future<void> future_pool[] = {
      async(q_push_lambda, "aaa", 64),  async(q_push_lambda, "bbb", 128),
      async(q_push_lambda, "ccc", 4),   async(q_push_lambda, "xxx", 512),
      async(q_push_lambda, "zzz", 256),
  };

  for (auto& one_future : future_pool) {
    one_future.get();  // no result but block till the end of exceution

    cout << "future is returned" << endl;
  }

  auto q_pop_future = async(q_pop_lambda);
  q_pop_future.get();  // no result but block till the end of exceution

  cout << "number of q pop = " << q_pop_count << endl;
  cout << "end of block" << endl;
  cout << "----- -----" << endl;
}
