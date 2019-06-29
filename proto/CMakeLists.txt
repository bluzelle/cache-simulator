protobuf_generate_cpp(PROTO_SRC PROTO_HEADER actors.proto kcache.proto cache_request.proto)
add_library(proto ${PROTO_HEADER} ${PROTO_SRC})
set_target_properties(proto PROPERTIES COMPILE_FLAGS "-Wno-unused")
