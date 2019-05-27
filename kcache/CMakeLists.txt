add_library(kcache STATIC
        knode.hpp
        knode.cpp
        )

target_link_libraries(kcache actors models)
