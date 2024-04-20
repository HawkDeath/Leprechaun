#ifndef LEPRECHAUN_LOGGER_H
#define LEPRECHAUN_LOGGER_H

#include <spdlog/sinks/basic_file_sink.h>
#include <memory>

namespace Leprechaun
{
    class Logger
    {
    public:
        template<typename FormatString, typename... Args>
        static void print_info(const FormatString &fmt, Args&&...args);

        template<typename FormatString, typename... Args>
        static void print_error(const FormatString &fmt, Args&&...args);

        template<typename FormatString, typename... Args>
        static void print_warning(const FormatString &fmt, Args&&...args);

        static std::string default_logger_name()  { return "leprechaun-logger"; }

    private:
        static std::shared_ptr<spdlog::logger> logger_handle;
    };
}

#endif //LEPRECHAUN_LOGGER_H
