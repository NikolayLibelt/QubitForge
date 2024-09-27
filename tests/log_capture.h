#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/expressions/formatters/format.hpp>
#include <boost/make_shared.hpp>
#include <sstream>

class LogCapture
{
public:
    LogCapture()
    {
        logging_stream_ = boost::make_shared<std::ostringstream>();

        sink_ = boost::make_shared<sink_t>();
        sink_->locked_backend()->add_stream(logging_stream_);

        sink_->set_formatter(boost::log::expressions::stream << boost::log::expressions::smessage);

        boost::log::core::get()->add_sink(sink_);
    }

    ~LogCapture()
    {
        boost::log::core::get()->remove_sink(sink_);
    }

    std::string get_logs()
    {
        return logging_stream_->str();
    }

private:
    using sink_t = boost::log::sinks::synchronous_sink<boost::log::sinks::text_ostream_backend>;
    boost::shared_ptr<sink_t> sink_;
    boost::shared_ptr<std::ostringstream> logging_stream_;
};
