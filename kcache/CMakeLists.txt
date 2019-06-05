add_library(kcache STATIC
        knode.hpp
        knode.cpp
        kademlia_global_state.cpp
        kademlia_global_state.hpp
        kademlia_routing_table.hpp
        kademlia_routing_table.cpp
        kcache_client.cpp
        kcache_client.hpp
        )

target_link_libraries(kcache actors models proto random ${Protobuf_LIBRARIES})
target_include_directories(kcache PRIVATE ${PROTO_INCLUDE_DIR})
add_dependencies(kcache proto)
