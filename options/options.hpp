#pragma once
#include <jsoncpp/json/json.h>

namespace ksim
{
    class options
    {
    public:
        void merge(const std::string filename);

        const Json::Value& get() const;

    private:
        void recursive_merge(Json::Value& dest, Json::Value& src);
        Json::Value data;
    };
}

