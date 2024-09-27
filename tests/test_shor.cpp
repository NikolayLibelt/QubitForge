#include <gtest/gtest.h>
#include "shor.h"
#include "log_capture.h"
#include "logger.h"

TEST(ShorAlgorithmTest, CompositeNumber)
{
    Logger::init_logging();
    LogCapture log_capture;

    ShorAlgorithm::run(15);

    std::string output = log_capture.get_logs();
    EXPECT_TRUE(output.find("Делители: 3 и 5") != std::string::npos);
}

TEST(ShorAlgorithmTest, PrimeNumber)
{
    Logger::init_logging();
    LogCapture log_capture;

    ShorAlgorithm::run(13);

    std::string output = log_capture.get_logs();
    EXPECT_TRUE(output.find("Простое число.") != std::string::npos);
}
