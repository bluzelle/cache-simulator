add_library(options STATIC
        options.hpp options.cpp)

target_link_libraries(options ${JSONCPP_LIBRARIES})