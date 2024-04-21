//#include "Log/Logger.h"
//
//#include <spdlog/sinks/basic_file_sink.h>
//#include <spdlog/async.h>
//
//namespace Leprechaun
//{
//    Logger::Logger()
//    {
//        logger_handle = spdlog::basic_logger_mt<spdlog::async_factory>(default_logger_name(), "logs/log.txt");
//    }
//
//    template<typename FormatString, typename ...Args>
//    void Logger::print_info(const FormatString &fmt, Args &&...args) {
//        logger_handle->info(fmt, std::forward<Args>(args)...);
//    }
//
//    template<typename FormatString, typename ...Args>
//    void Logger::print_error(const FormatString &fmt, Args &&...args) {
//        logger_handle->error(fmt, std::forward<Args>(args)...);
//    }
//
//    template<typename FormatString, typename ...Args>
//    void Logger::print_warning(const FormatString &fmt, Args &&...args) {
//        logger_handle->warn(fmt, std::forward<Args>(args)...);
//    }
//}