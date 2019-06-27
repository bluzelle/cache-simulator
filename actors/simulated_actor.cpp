#include <actors/simulated_actor.hpp>
#include <actors/actor_system.hpp>
#include <assert.h>
#include <proto/actors.pb.h>

using namespace ksim;

simulated_actor::simulated_actor(actor_system& system)
        : id(system.register_actor(this))
        , location(system.location.pick_location())
        , system(system)
{
}

void
simulated_actor::handle_message(const ksim::userspace_message_t& /*msg*/)
{
    throw std::runtime_error("message not handled by any activity and default handler not defined");
}

void
simulated_actor::recieve_message_at(unsigned long time, const simulator_message_t& msg)
{
    assert(time > this->last_processed_time);

    this->ensure_message_set_exists(time);

    std::shared_lock<std::shared_mutex> lock(this->pending_messages_lock);
    std::lock_guard<std::mutex> lock2(this->pending_messages.at(time).second);

    this->pending_messages.at(time).first.push_back(msg);
}

void
simulated_actor::ensure_message_set_exists(unsigned long time)
{
    bool exists;
    {
        std::shared_lock lock(this->pending_messages_lock);
        exists = this->pending_messages.count(time) != 0;
    }

    if (!exists)
    {
        std::lock_guard<std::shared_mutex> lock(this->pending_messages_lock);
        this->pending_messages[time];
    }
}

void
simulated_actor::send(actor_id_t target, const simulator_message_t& msg, unsigned long delay)
{
    this->system.send(this->last_processed_time + delay, this->id, target, msg);
}

void
simulated_actor::send(actor_id_t target, const userspace_message_t& msg, unsigned long delay)
{
    simulator_message_t env;
    env.set_allocated_raw(new userspace_message_t(msg));
    this->send(target, env, delay);
}

void
simulated_actor::process_messages_at(unsigned long time)
{
    assert(time > this->last_processed_time);
    this->last_processed_time = time;

    std::list<simulator_message_t> msgs;

    {
        std::shared_lock lock(this->pending_messages_lock);
        msgs = this->pending_messages.at(time).first;
        this->pending_messages.erase(time);
    }

    for (const auto& msg : msgs)
    {
        this->deliver_message(msg);
    }
}

void simulated_actor::deliver_message(const ksim::simulator_message_t& msg)
{
    this->outer_current_message = msg;
    switch (msg.payload_case())
    {
        case envelope::kTimer: 
        {
            auto timer = msg.timer();
            if (this->running_timers.count(timer.id()) == 0) {
                throw std::runtime_error("no such timer");
            }

            this->running_timers[timer.id()]();
            this->running_timers.erase(timer.id());
            break;
        }
        case envelope::kActivityMessage:
        {
            auto owner = msg.activity_message().owner();
            auto id = msg.activity_message().activity();
            auto raw = msg.activity_message().payload();

            if (owner == this->id) {
                if (this->running_activities.count(id) > 0) {
                    this->running_activities.at(id)->handle_message(raw);
                }
                // else drop the message: it goes to an activity that has already been wrapped up
            } else {
                this->deliver_raw(raw);
            }
            break;
        }
        case envelope::kRaw:
            this->deliver_raw(msg.raw());
            break;
        case envelope::PAYLOAD_NOT_SET:
            throw std::runtime_error("trying to deliver empty message");
            break;
    }
    this->outer_current_message = simulator_message_t();
}

void
simulated_actor::deliver_raw(const userspace_message_t& msg)
{
    this->current_message = msg;
    unsigned int handled = 0;

    for (const auto& pair: this->running_activities)
    {
        if(pair.second->handles_message(msg))
        {
            pair.second->handle_message(msg);
            handled++;
        }
    }

    if (handled > 1)
    {
        throw std::runtime_error("duplicate handlers");
    }

    if (handled == 0)
    {
        this->handle_message(msg);
    }

    this->current_message = userspace_message_t();
}

void 
simulated_actor::start_timer(unsigned long time, std::function<void()> callback)
{
    auto id = this->next_timer_id++;
    simulator_message_t msg;
    msg.mutable_timer()->set_id(id);
    
    this->running_timers[id] = callback;
    this->send(this->id, msg, time);
}

void
simulated_actor::start()
{

}

void
simulated_actor::finalize()
{

}

unsigned long
simulated_actor::current_time()
{
    return this->last_processed_time;
}
