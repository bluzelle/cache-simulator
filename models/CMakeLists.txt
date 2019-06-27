add_library(models STATIC
        latency_model.hpp
        latency_model.cpp
        location_model.cpp
        location_model.hpp
        )

target_link_libraries(models proto ${Protobuf_LIBRARIES})
target_include_directories(models PRIVATE ${PROTO_INCLUDE_DIR})
