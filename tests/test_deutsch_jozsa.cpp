#include <gtest/gtest.h>
#include "deutsch_jozsa.h"
#include "log_capture.h"
#include "logger.h"

TEST(DeutschJozsaTest, ConstantFunction)
{
    Logger::init_logging();
    LogCapture log_capture;

    DeutschJozsaAlgorithm::run([](int) { return 0; }, 2);

    std::string output = log_capture.get_logs();
    EXPECT_TRUE(output.find("Функция константная.") != std::string::npos);
}

TEST(DeutschJozsaTest, BalancedFunction)
{
    Logger::init_logging();
    LogCapture log_capture;

    DeutschJozsaAlgorithm::run([](int x) { return x % 2; }, 2);

    std::string output = log_capture.get_logs();
    EXPECT_TRUE(output.find("Функция сбалансированная.") != std::string::npos);
}
