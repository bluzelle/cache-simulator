add_library(actors STATIC
        simulated_actor.hpp
        simulated_actor.cpp
        actor_system.cpp
        actor_system.hpp
        activity.cpp
        activity.hpp)

target_link_libraries(actors proto log ${Protobuf_LIBRARIES} stdc++fs)
target_include_directories(actors PRIVATE ${PROTO_INCLUDE_DIR})
