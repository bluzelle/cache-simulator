#pragma once
#include <string>
#include <optional>
#include <options/options.hpp>

namespace ksim
{
    class log_base
    {
        class severity_lock
        {
        public:
            severity_lock(log_base* owner, unsigned int level);
            ~severity_lock();

            severity_lock(severity_lock&&) = default;
            severity_lock& operator=(severity_lock&&) = default;

            severity_lock(severity_lock&) = delete;
            severity_lock& operator=(severity_lock&) = delete;
        private:
            log_base* owner;
            unsigned int to_restore;
        };

        friend class log_root;
        friend class log_child;

    public:
        log_base(std::string name, std::optional<unsigned int> severity = std::nullopt);
        virtual ~log_base() = default;

        void say(const std::string& message, std::optional<unsigned int> severity = std::nullopt);
        void ingest(const std::string& message);

        log_base& operator<<(const std::string& str);
        log_base& operator<<(const char* str);

        template <typename T>
        log_base& operator<<(T t)
        {
            this->ingest(std::to_string(t));
            return *this;
        }

        void set_prefix(const std::string& str);

        severity_lock with_severity(unsigned int);


    protected:
        virtual void say(const std::string& message, const std::string& prefix, unsigned int severity) = 0;

        std::string name;

        std::string buffer;

        const unsigned int default_severity;
        unsigned int current_severity;
    };

    class log_root : public log_base
    {
    public:
        log_root(std::string name, const ksim::options& options, std::optional<unsigned int> severity = std::nullopt);
        void say(const std::string& message, std::optional<unsigned int> severity = std::nullopt);

    private:
        const ksim::options& options;
        void say(const std::string& message, const std::string& prefix, unsigned int severity) override;
    };

    class log_child : public log_base
    {
    public:
        log_child(std::string name, log_base& parent, std::optional<unsigned int> severity = std::nullopt);
        void say(const std::string& message, std::optional<unsigned int> severity = std::nullopt);

    private:
        log_base& parent;
        void say(const std::string& message, const std::string& prefix, unsigned int severity) override;
    };
}
