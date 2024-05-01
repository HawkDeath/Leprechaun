#ifndef LEPRECHAUN_LOGGER_H
#define LEPRECHAUN_LOGGER_H


#include <memory>
#include <string>
#include <cstdio>
#include <spdlog/spdlog.h>
namespace spdlog {
    class logger;
}

namespace Leprechaun
{
    class Logger
    {
    public:
        Logger();
        ~Logger() = default;

        template<typename FormatString, typename... Args>
        inline void print_info(const FormatString &fmt, Args&&...args) { logger_handle->info(fmt, std::forward<Args>(args)...);}

        template<typename FormatString, typename... Args>
        void print_error(const FormatString &fmt, Args&&...args) { logger_handle->error(fmt, std::forward<Args>(args)...);}

        template<typename FormatString, typename... Args>
        void print_warning(const FormatString &fmt, Args&&...args) { logger_handle->warn(fmt, std::forward<Args>(args)...);}

        std::string default_logger_name()  { return "leprechaun-logger"; }

        static Logger get_logger() { static Logger log; return log;}

    private:
        std::shared_ptr<spdlog::logger> logger_handle;
    };
}


#endif //LEPRECHAUN_LOGGER_H
