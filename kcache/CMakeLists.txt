add_library(kcache STATIC
        knode.hpp
        knode.cpp
        kademlia_global_state.cpp
        kademlia_global_state.hpp
        )

target_link_libraries(kcache actors models)
