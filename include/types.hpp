#pragma once
#include <string>
#include <proto/actors.pb.h>

namespace ksim
{
  using simulator_message_t = envelope;
  using userspace_message_t = user_envelope;
  using actor_id_t = unsigned int;
  using chunk_id_t = std::string;
}
