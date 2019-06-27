add_library(config STATIC
        sim_config.hpp
        sim_config.cpp)

target_link_libraries(config proto ${Protobuf_LIBRARIES})
target_include_directories(config PRIVATE ${PROTO_INCLUDE_DIR})
