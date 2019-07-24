add_library(kcache STATIC
        knode.hpp
        knode.cpp
        kcache_global_state.cpp
        kcache_global_state.hpp
        kademlia/kademlia_routing_table.hpp
        kademlia/kademlia_routing_table.cpp
        kademlia/kademlia_activity.cpp
        kademlia/kademlia_activity.hpp
        kclient.cpp
        kclient.hpp
        cache_node_activity.cpp
        cache_node_activity.hpp
        kcache_config.hpp kcache_config.cpp cache_client_activity.cpp cache_client_activity.hpp)

target_link_libraries(kcache actors models proto random ${Protobuf_LIBRARIES} stdc++fs)
target_include_directories(kcache PRIVATE ${PROTO_INCLUDE_DIR})
add_dependencies(kcache proto)
