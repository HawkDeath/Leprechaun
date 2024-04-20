#ifndef LEPRECHAUN_LOGGER_H
#define LEPRECHAUN_LOGGER_H

#include <memory>
#include <string>

namespace spdlog {
    class logger;
}
namespace Leprechaun
{
    class Logger
    {
    public:
        Logger();

        template<typename FormatString, typename... Args>
        void print_info(const FormatString &fmt, Args&&...args);

        template<typename FormatString, typename... Args>
        void print_error(const FormatString &fmt, Args&&...args);

        template<typename FormatString, typename... Args>
        void print_warning(const FormatString &fmt, Args&&...args);

        std::string default_logger_name()  { return "leprechaun-logger"; }

    private:
        std::shared_ptr<spdlog::logger> logger_handle;
    };
    static Logger get_logger() { static Logger log; return log;}
}


#endif //LEPRECHAUN_LOGGER_H
