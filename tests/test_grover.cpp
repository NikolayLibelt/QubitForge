#include <gtest/gtest.h>
#include "grover.h"
#include "log_capture.h"
#include "logger.h"

TEST(GroverAlgorithmTest, FindState)
{
    Logger::init_logging();
    LogCapture log_capture;

    GroverAlgorithm::run(2, 3);

    std::string output = log_capture.get_logs();
    EXPECT_TRUE(output.find("Найденное состояние: 3") != std::string::npos);
}
