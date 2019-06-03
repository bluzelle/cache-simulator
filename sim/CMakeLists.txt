add_library(simulation STATIC simulation.cpp simulation.hpp)
target_link_libraries(simulation actors models kcache config proto Threads::Threads)
target_include_directories(simulation PRIVATE ${PROTO_INCLUDE_DIR})

add_executable(sim main.cpp)
add_dependencies(sim proto)
target_link_libraries(sim simulation)
target_include_directories(sim PRIVATE ${PROTO_INCLUDE_DIR})
