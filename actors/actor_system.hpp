#pragma once
#include <include/types.hpp>

namespace ksim
{
  class actor_system
  {
    using actor_id int;

    void send(actor_id, message_t);
  }
}
