#pragma once
#include <include/types.hpp>
#include <mutex>
#include <shared_mutex>

namespace ksim
{
  using message_handler std::function<const message_t&, actor_system&>;

  class simulated_actor
  {
    simulated_actor(void* message_handler);

    // does messaging, time steps, etc
    void process_messages_at(int time);
    void recieve_message_at(int time, message_t msg);
    
    int last_processed_time = 0;
    std::map<int, std::pair<std::list<message_t>, std::mutex>> pending_messages;
    std::shared_mutex pending_messages_lock;
  }
}
