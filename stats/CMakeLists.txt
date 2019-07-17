add_library(stats STATIC
        statistic.cpp statistic.hpp
        collection_stat.hpp
        statistic_set.cpp statistic_set.hpp
        set_frequency_counter.cpp set_frequency_counter.hpp
        frequency_counter.cpp frequency_counter.hpp
        xy_plot_statistic.cpp xy_plot_statistic.hpp
        )

target_link_libraries(stats stdc++fs)
