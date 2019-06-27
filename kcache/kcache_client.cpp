#include <kcache/kcache_client.hpp>
#include <proto/kcache.pb.h>

using namespace ksim::kcache;

kcache_client::kcache_client(ksim::actor_system& system, const ksim::client_spec& spec)
    : simulated_actor(system)
    , spec(spec)
{
}

//void kcache_client::handle_message(const ksim::message_t& msg)
//{
//    kcache_message parsed;
//    parsed.ParseFromString(msg);
//
//    switch (parsed.payload_case())
//    {
//        case kcache_message::kTimer:
//            if(parsed.timer().type() == "start" || parsed.timer().type() == "request")
//            {
//                this->do_request();
//            }
//            break;
//    }
//}

void kcache_client::do_request()
{
    // TODO
}

void kcache_client::start()
{
    kcache_message delay;
    delay.mutable_timer()->set_type("start");
    //this->send_delayed(this->id, delay.SerializeAsString(), this->rand.next_int_inclusive(this->spec.start_time_min, this->spec.start_time_max));

    // define a "activity" concept that isloates messages responsible for a single logical operation
    // i.e. init, lookup, maintaining a chunk
}
