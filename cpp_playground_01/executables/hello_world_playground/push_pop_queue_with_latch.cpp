#include <future>
#include <iostream>
#include <latch>
#include <map>
#include <queue>
#include <string>
#include <thread>

void push_pop_queue_with_latch() {
  using namespace std;
  cout << "----- -----" << endl;
  cout << "start of block push_pop_queue_with_latch" << endl;

  auto q = std::queue<int>{};
  auto q_mtx = mutex{};

  auto q_push_lambda = [&q, &q_mtx](auto name, auto base, latch& lat) -> void {
    for (auto i : {1, 2, 4, 5, 7, 8}) {
      auto val = base + i;
      cout << name << ": push " << val << " to q" << endl;
      q_mtx.lock();
      q.push(val);
      q_mtx.unlock();
    }
    lat.count_down();
  };

  auto q_pop_count = 0;
  auto q_pop_count_mtx = mutex{};

  auto q_pop_lambda = [&q, &q_mtx, &q_pop_count,
                       &q_pop_count_mtx](latch& lat) -> void {
    while (!lat.try_wait() || !q.empty()) {
      if (q.empty()) {
        continue;
      }
      cout << "queue not empty" << endl;
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

  const int number_of_producers = 5;

  auto lat = latch{number_of_producers};
  auto thread_sack = map<string, thread*>{};

  auto num_base = 64;
  for (auto i = 0; i < number_of_producers; i++) {
    auto name = "producer_thread " + to_string(i);
    auto val = num_base * (i + 1);
    thread_sack.insert({
        name,
        new thread{q_push_lambda, name, val, ref(lat)},
    });
  }

  auto pop_thread = jthread{q_pop_lambda, ref(lat)};

  for (auto&& one_thread_wrap : thread_sack) {
    cout << "waiting for thread " << one_thread_wrap.first << " to join"
         << endl;
    one_thread_wrap.second->join();
    cout << "thread " << one_thread_wrap.first << " is joined " << endl;
    // free memory
    delete one_thread_wrap.second;
    one_thread_wrap.second = nullptr;
  }

  // wait pop thread to end

  cout << "waiting for pop thread to join " << endl;
  pop_thread.join();
  cout << "pop thread is joined " << endl;

  cout << "number of q pop = " << q_pop_count << endl;
  cout << "end of block" << endl;
  cout << "----- -----" << endl;
}
