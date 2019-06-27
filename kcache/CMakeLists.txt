add_library(kcache STATIC
        knode.hpp
        knode.cpp
        kademlia/kademlia_global_state.cpp
        kademlia/kademlia_global_state.hpp
        kademlia/kademlia_routing_table.hpp
        kademlia/kademlia_routing_table.cpp
        kademlia/kademlia_activity.cpp kademlia/kademlia_activity.hpp)

target_link_libraries(kcache actors models proto random ${Protobuf_LIBRARIES})
target_include_directories(kcache PRIVATE ${PROTO_INCLUDE_DIR})
add_dependencies(kcache proto)
