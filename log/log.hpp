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

    private:

        void say(const std::string& message, const std::string& prefix);

        const std::string name;
        const std::optional<log*> parent;
    };
}
