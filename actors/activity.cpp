#include <actors/activity.hpp>
#include <actors/simulated_actor.hpp>

using namespace ksim;

bool
activity::handles_message(const ksim::message_t& /*msg*/)
{
    return false;
}

void
activity::send_message(ksim::actor_id_t target, const ksim::message_t &msg, unsigned long delay)
{
}

void
activity::done()
{
    this->owner->running_activities.erase(this->id);
}
