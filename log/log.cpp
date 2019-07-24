#include <log/log.hpp>
#include <iostream>

using namespace ksim;

log_base::log_base(std::string name, std::optional<unsigned int> severity)
    : name(name)
    , default_severity(severity.has_value() ? severity.value() : 3)
    , current_severity(this->default_severity)
{}

void log_base::say(const std::string& message, std::optional<unsigned int> severity)
{
    this->say(message, "", severity.has_value() ? severity.value() : this->current_severity);
}

// I am very confused about why these are necessary...
void log_child::say(const std::string& message, std::optional<unsigned int> severity)
{
    this->say(message, "", severity.has_value() ? severity.value() : this->current_severity);
}
void log_root::say(const std::string& message, std::optional<unsigned int> severity)
{
    this->say(message, "", severity.has_value() ? severity.value() : this->current_severity);
}

void
log_base::ingest(const std::string& message)
{
    this->buffer += message;
    auto loc = this->buffer.find("\n");
    if (loc == std::string::npos){
        return;
    }

    this->say(this->buffer.substr(0, loc), this->current_severity);
    this->buffer = this->buffer.substr(loc+1, this->buffer.size());
    this->ingest("");
}

ksim::log_base&
log_base::operator<<(const std::string& str)
{
    this->ingest(str);
    return *this;
}

ksim::log_base&
log_base::operator<<(const char* str)
{
    this->ingest(std::string(str));
    return *this;
}

void
log_base::set_prefix(const std::string& str)
{
    this->name = str;
}

log_base::severity_lock::severity_lock(log_base* owner, unsigned int val)
    : owner(owner)
{
    this->to_restore = this->owner->current_severity;
    this->owner->current_severity = val;
}

log_base::severity_lock::~severity_lock()
{
    this->owner->current_severity = this->to_restore;
}

log_base::severity_lock log_base::with_severity(unsigned int level)
{
    return severity_lock(this, level);
}

log_root::log_root(std::string name, const ksim::options& options, std::optional<unsigned int> severity)
    : log_base(name, severity)
    , options(options)
{
}

void log_root::say(const std::string& message, const std::string& prefix, unsigned int severity)
{
    if (severity < this->options.get()["log_severity"].asUInt())
    {
        return;
    }

    std::string my_prefix = this->name + "|" + prefix;
    my_prefix = std::to_string(severity) + "|" + my_prefix;

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

        start_index = end_index + 1;
    }

    std::cout << result;
}


log_child::log_child(std::string name, ksim::log_base& parent, std::optional<unsigned int> severity)
    : log_base(name, severity.has_value() ? severity : parent.default_severity)
    , parent(parent)
{
}

void log_child::say(const std::string& message, const std::string& prefix, unsigned int severity)
{
    std::string my_prefix = this->name + "|" + prefix;
    this->parent.say(message, my_prefix, severity);
}
