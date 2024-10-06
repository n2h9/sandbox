#pragma once

namespace our_project {
namespace networking_tools {

int push_pop_queue_with_async(const int&& number_of_producers);

int push_pop_queue_with_jthread(const int&& number_of_producers);

int push_pop_queue_with_latch(const int&& number_of_producers);

void some_semaphore_stuff();

}  // namespace networking_tools
}  // namespace our_project