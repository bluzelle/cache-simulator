#include <actors/activity.hpp>
#include <actors/simulated_actor.hpp>
#include <proto/actors.pb.h>

using namespace ksim;

bool
activity::handles_message(const ksim::userspace_message_t& /*msg*/)
{
    return false;
}

void
activity::send_activity_message(ksim::actor_id_t target, const ksim::userspace_message_t &msg)
{
    simulator_message_t env;
    env.mutable_activity_message()->set_activity(this->id);
    env.mutable_activity_message()->set_owner(this->owner->id);
    env.mutable_activity_message()->set_allocated_payload(new userspace_message_t(msg));

    owner->send(target, env);
}

void
activity::reply_in_context(const ksim::userspace_message_t &msg)
{
    const auto& query = owner->outer_current_message.activity_message();

    if (query.owner() == this->owner->id)
    {
        throw std::runtime_error("replying to self?");
    }

    simulator_message_t env;

    env.mutable_activity_message()->set_activity(query.activity());
    env.mutable_activity_message()->set_owner(query.owner());

    env.mutable_activity_message()->set_allocated_payload(new userspace_message_t(msg));

    owner->send(query.owner(), env);
}

void
activity::done()
{
    this->owner->running_activities.erase(this->id);
}
