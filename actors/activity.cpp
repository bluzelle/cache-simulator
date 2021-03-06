#include <actors/activity.hpp>
#include <actors/simulated_actor.hpp>
#include <proto/actors.pb.h>
#include <stats/frequency_counter.hpp>

using namespace ksim;

activity::activity(ksim::simulated_actor *owner, unsigned int id, const std::string& name)
    : log("activity" + std::to_string(id), (owner->log), 2)
    , owner(owner)
    , id(id)
    , name(name)
{
}

void
activity::send_activity_message(ksim::actor_id_t target, const ksim::userspace_message_t &msg)
{
    simulator_message_t env;
    env.mutable_activity_message()->set_activity(this->id);
    env.mutable_activity_message()->set_owner(this->owner->id);
    env.mutable_activity_message()->set_allocated_payload(new userspace_message_t(msg));
    env.mutable_activity_message()->set_sender(this->owner->id);

    this->stats().stat<frequency_counter>("activity " + this->name + " new messages sent").tick();

    owner->send(target, env);
}

void
activity::reply_in_context(const ksim::userspace_message_t &msg)
{
    const auto& query = owner->outer_current_message.activity_message();

    if (query.sender() == this->owner->id)
    {
        throw std::runtime_error("replying to self?");
    }

    simulator_message_t env;

    env.mutable_activity_message()->set_activity(query.activity());
    env.mutable_activity_message()->set_owner(query.owner());
    env.mutable_activity_message()->set_sender(this->owner->id);

    env.mutable_activity_message()->set_allocated_payload(new userspace_message_t(msg));

    this->stats().stat<frequency_counter>("activity " + this->name + " in context replies sent").tick();

    owner->send(query.sender(), env);
}

void
activity::done()
{
    this->owner->running_activities.erase(this->id);
}

unsigned long
activity::current_time()
{
    return this->owner->current_time();
}

actor_id_t
activity::address()
{
    return this->owner->id;
}

void
activity::start_timer(unsigned long delay, std::function<void()> callback)
{
    owner->start_timer(delay, callback);
}

bool
activity::handles_message(const ksim::userspace_message_t &/*msg*/)
{
    return false;
}

void
activity::finalize()
{
}

statistic_set& activity::stats()
{
    return this->owner->stats();
}


