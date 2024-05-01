#include "Log/Logger.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>

#include <vector>

namespace Leprechaun {
    Logger::Logger() {
        std::vector<spdlog::sink_ptr> sinks;
        sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        sinks.push_back(std::make_shared<spdlog::sinks::daily_file_sink_mt>("logs/log.txt", 23, 59));
        logger_handle = std::make_shared<spdlog::logger>(default_logger_name(), sinks.begin(), sinks.end());
        spdlog::register_logger(logger_handle);
    }
/*
    template<typename FormatString, typename ...Args>
    inline void Logger::print_info(const FormatString &fmt, Args &&...args) {
        //   logger_handle->info(fmt, std::forward<Args>(args)...);
        spdlog::info(fmt, std::forward<Args>(args)...);
    }

    template<typename FormatString, typename ...Args>
    void Logger::print_error(const FormatString &fmt, Args &&...args) {
        //    logger_handle->error(fmt, std::forward<Args>(args)...);
        spdlog::error(fmt, std::forward<Args>(args)...);
    }

    template<typename FormatString, typename ...Args>
    void Logger::print_warning(const FormatString &fmt, Args &&...args) {
        //   logger_handle->warn(fmt, std::forward<Args>(args)...);
        spdlog::warn(fmt, std::forward<Args>(args)...);
    }*/
}
