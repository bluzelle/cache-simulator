add_library(config STATIC
        sim_config.hpp
        sim_config.cpp alg_specific_config.hpp)

target_link_libraries(config proto ${Protobuf_LIBRARIES} stdc++fs)
target_include_directories(config PRIVATE ${PROTO_INCLUDE_DIR})
