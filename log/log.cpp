#include <log/log.hpp>
#include <iostream>

using namespace ksim;

log::log(std::string name, std::optional<ksim::log*> parent)
    : name(name)
    , parent(parent)
{}

void log::say(const std::string& message)
{
    this->say(message, "");
}

void log::say(const std::string& message, const std::string& prefix)
{
    std::string my_prefix = "[" + this->name + "]" + prefix;

    if(this->parent.has_value())
    {
        this->parent.value()->say(message, my_prefix);
        return;
    }

    std::string result;

    size_t start_index = 0;
    size_t end_index;
    while(start_index < message.size())
    {
        auto loc = message.find("\n", start_index);
        if(loc == std::string::npos)
        {
            end_index = message.size();
        }
        else
        {
            end_index = loc;
        }

        result += my_prefix;
        result += " ";
        result += message.substr(start_index, end_index - start_index);
        result += "\n";

        start_index = end_index;
    }

    std::cout << result;
}

void
log::ingest(const std::string& message)
{
    this->buffer += message;
    auto loc = this->buffer.find("\n");
    if (loc == std::string::npos){
        return;
    }

    this->say(this->buffer.substr(0, loc));
    this->buffer = this->buffer.substr(loc+1, this->buffer.size());
    this->ingest("");
}

ksim::log&
log::operator<<(const std::string& str)
{
    this->ingest(str);
    return *this;
}

ksim::log&
log::operator<<(const char* str)
{
    this->ingest(std::string(str));
    return *this;
}
