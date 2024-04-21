#ifndef LEPRECHAUN_LOGGER_H
#define LEPRECHAUN_LOGGER_H


#include <string>
#include "spdlog/include/spdlog/spdlog.h" // FIXME: temporary solution. Find a new solution to for logger


namespace Leprechaun
{
    class Logger
    {
    public:
        Logger() = default;
        ~Logger() = default;

        template<typename FormatString, typename... Args>
        void print_info(const FormatString &fmt, Args&&...args) { spdlog::info(fmt, std::forward<Args>(args)...); }

        template<typename FormatString, typename... Args>
        void print_error(const FormatString &fmt, Args&&...args) { spdlog::error(fmt, std::forward<Args>(args)...); }

        template<typename FormatString, typename... Args>
        void print_warning(const FormatString &fmt, Args&&...args) { spdlog::warn(fmt, std::forward<Args>(args)...); }

        std::string default_logger_name()  { return "leprechaun-logger"; }

    private:
    };
    static Logger get_logger() { static Logger log; return log;}
}


#endif //LEPRECHAUN_LOGGER_H
