add_library(simulation STATIC simulation.cpp simulation.hpp)
add_executable(sim main.cpp)
target_link_libraries(sim actors models simulation kcache Threads::Threads)
