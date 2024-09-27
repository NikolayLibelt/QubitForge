#pragma once

#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <string>

class Logger
{
public:
    static void init_logging();

    static void log_trace(const std::string& message);
    static void log_debug(const std::string& message);
    static void log_info(const std::string& message);
    static void log_warning(const std::string& message);
    static void log_error(const std::string& message);
    static void log_fatal(const std::string& message);
};
