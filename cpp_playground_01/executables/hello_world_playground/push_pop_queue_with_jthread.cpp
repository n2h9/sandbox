#include <exception>
#include <future>
#include <iostream>
#include <queue>
#include <thread>

void push_pop_queue_with_jthread() {
  using namespace std;
  cout << "----- -----" << endl;
  cout << "start of block push_pop_queue_with_jthread" << endl;

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

  thread thread_pool[] = {
      thread{q_push_lambda, "aaa", 64},
      thread{q_push_lambda, "bbb", 128},
      thread{q_push_lambda, "ccc", 4},
  };

  // jthread t1{q_push_lambda, "aaa", 64};
  // jthread t2{q_push_lambda, "bbb", 128};
  // jthread t3{q_push_lambda, "ccc", 4};

  // this_thread::sleep_for(chrono::seconds{4});

  for (auto& t : thread_pool) {
    t.join();
    cout << "thread is joined" << endl;
  }

  // thread_pool[0].join();
  // thread_pool[1].join();
  // thread_pool[2].join();

  // t1.join();
  // t2.join();
  // t3.join();

  pop_thread.request_stop();
  pop_thread.join();

  cout << "number of q pop = " << q_pop_count << endl;
  cout << "end of block" << endl;
  cout << "----- -----" << endl;
}
