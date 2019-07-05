#pragma once
#include <string>
#include <optional>

namespace ksim
{
    class log
    {
    public:
        log(std::string name, std::optional<log*> parent = std::nullopt);

        void say(const std::string& message);
        void ingest(const std::string& message);

        log& operator<<(const std::string& str);
        log& operator<<(const char* str);

        template <typename T>
        log& operator<<(T t)
        {
            this->ingest(std::to_string(t));
            return *this;
        }

    private:

        void say(const std::string& message, const std::string& prefix);

        const std::string name;
        const std::optional<log*> parent;

        std::string buffer;
    };

}
