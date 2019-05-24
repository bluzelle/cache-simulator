#include <actors/simulated_actor.hpp>

using namespace ksim;

simulated_actor::recieve_message_at(int time, const message_t& msg)
{
  this->ensure_message_set_exists(time);

  std::shared_lock lock(this->pending_messages_lock);
  std::lock lock(this->pending_messages.at(time).first);
  this->pending_messages.at(time).second.emplace(msg);
}

simulated_actor::ensure_message_set_exists(int time)
{
  bool exists;
  {
    std::shared_lock lock(this->pending_messages_lock);
    exists = this->pending_messages.count(time) != 0;
  }

  if (!exists)
  {
    std::exclusive_lock lock(this->pending_messages_lock);
    this->pending_messages[time];
  }
}
