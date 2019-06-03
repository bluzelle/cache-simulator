add_library(kcache STATIC
        knode.hpp
        knode.cpp
        kademlia_global_state.cpp
        kademlia_global_state.hpp
        kademlia_routing_table.hpp
        kademlia_routing_table.cpp
        )

target_link_libraries(kcache actors models proto random)
add_dependencies(kcache proto)
target_include_directories(kcache PRIVATE ${PROTO_INCLUDE_DIR})
