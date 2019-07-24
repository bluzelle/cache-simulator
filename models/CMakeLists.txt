add_library(models STATIC
        latency_model.hpp
        latency_model.cpp
        location_model.cpp
        location_model.hpp
        client_model.cpp client_model.hpp
        client_work_spec.hpp
        client_models/eve_client_type.cpp client_models/eve_client_type.hpp
        client_models/fortnite_region_client_type.hpp client_models/fortnite_region_client_type.cpp
        client_models/fortnite_session_client_type.hpp client_models/fortnite_session_client_type.cpp
        client_models/matchmaking_lobby_client_type.hpp client_models/matchmaking_lobby_client_type.cpp
        client_models/random_client_type.cpp client_models/random_client_type.hpp
        client_models/region_model.cpp client_models/region_model.hpp
        client_models/weather_client_type.cpp client_models/weather_client_type.hpp)


target_link_libraries(models proto ${Protobuf_LIBRARIES} stdc++fs)
target_include_directories(models PRIVATE ${PROTO_INCLUDE_DIR})
