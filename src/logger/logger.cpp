#include "logger.h"
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/support/date_time.hpp>

using boost::log::expressions::format_date_time;

void Logger::init_logging()
{
    boost::log::add_file_log("detailed_logfile.log");

    boost::log::add_common_attributes();

    boost::log::add_console_log(
        std::cout, boost::log::keywords::format =
                       boost::log::expressions::stream
                       << "[" << format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S")
                       << "]: " << boost::log::expressions::smessage);
}

void Logger::log_trace(const std::string& message)
{
    BOOST_LOG_TRIVIAL(trace) << message;
}

void Logger::log_debug(const std::string& message)
{
    BOOST_LOG_TRIVIAL(debug) << message;
}

void Logger::log_info(const std::string& message)
{
    BOOST_LOG_TRIVIAL(info) << message;
}

void Logger::log_warning(const std::string& message)
{
    BOOST_LOG_TRIVIAL(warning) << message;
}

void Logger::log_error(const std::string& message)
{
    BOOST_LOG_TRIVIAL(error) << message;
}

void Logger::log_fatal(const std::string& message)
{
    BOOST_LOG_TRIVIAL(fatal) << message;
}
