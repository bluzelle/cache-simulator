#include <actors/activity.hpp>
#include <actors/simulated_actor.hpp>
#include <proto/actors.pb.h>

using namespace ksim;

bool
activity::handles_message(const ksim::message_t& /*msg*/)
{
    return false;
}

void
activity::send_message(ksim::actor_id_t target, const ksim::message_t &msg, unsigned long delay)
{
    envelope env;
    env.mutable_activity_message()->set_activity(this->id);
    env.mutable_activity_message()->set_owner(this->owner->id);
    env.mutable_activity_message()->set_payload(msg);
    
    owner->send(target, env, )
}

void
activity::done()
{
    this->owner->running_activities.erase(this->id);
}
