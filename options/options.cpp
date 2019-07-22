#include <options/options.hpp>
#include <fstream>

using namespace ksim;

void options::merge(const std::string filename)
{
    std::ifstream ifs(filename);
    Json::Reader reader;
    Json::Value read;
    reader.parse(ifs, read);

    this->recursive_merge(this->data, read);
}

const Json::Value& options::get() const
{
    return this->data;
}

void options::recursive_merge(Json::Value& dest, Json::Value& src)
{
    if(src.isObject())
    {
        for(const auto& key : src.getMemberNames())
        {
            this->recursive_merge(dest[key], src[key]);
        }
    }
    else
    {
        dest = src;
    }
}
