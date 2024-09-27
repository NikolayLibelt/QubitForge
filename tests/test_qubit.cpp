#include <gtest/gtest.h>
#include "qubit.h"
#include "log_capture.h"
#include "logger.h"

TEST(QubitTest, DefaultConstructor)
{
    Logger::init_logging();
    LogCapture log_capture;

    Qubit qubit;
    EXPECT_EQ(qubit.get_alpha(), std::complex<double>(1, 0));
    EXPECT_EQ(qubit.get_beta(), std::complex<double>(0, 0));
}

TEST(QubitTest, CustomConstructorNormalization)
{
    Logger::init_logging();
    LogCapture log_capture;

    Qubit qubit({3, 0}, {4, 0});
    double norm = std::norm(qubit.get_alpha()) + std::norm(qubit.get_beta());
    EXPECT_NEAR(norm, 1.0, 1e-6);
}

TEST(QubitTest, SetStateNormalization)
{
    Logger::init_logging();
    LogCapture log_capture;

    Qubit qubit;
    qubit.set_state({0, 0}, {5, 0});
    double norm = std::norm(qubit.get_alpha()) + std::norm(qubit.get_beta());
    EXPECT_NEAR(norm, 1.0, 1e-6);
}

TEST(QubitTest, MeasureZeroState)
{
    Logger::init_logging();
    LogCapture log_capture;

    Qubit qubit;
    int result = qubit.measure();
    EXPECT_EQ(result, 0);
    EXPECT_EQ(qubit.get_alpha(), std::complex<double>(1, 0));
    EXPECT_EQ(qubit.get_beta(), std::complex<double>(0, 0));
}

TEST(QubitTest, MeasureOneState)
{
    Logger::init_logging();
    LogCapture log_capture;

    Qubit qubit({0, 0}, {1, 0});
    int result = qubit.measure();
    EXPECT_EQ(result, 1);
    EXPECT_EQ(qubit.get_alpha(), std::complex<double>(0, 0));
    EXPECT_EQ(qubit.get_beta(), std::complex<double>(1, 0));
}

TEST(QubitTest, MeasureSuperpositionState)
{
    Logger::init_logging();
    LogCapture log_capture;

    Qubit qubit({1 / std::sqrt(2), 0}, {1 / std::sqrt(2), 0});
    int zero_count = 0;
    int one_count = 0;
    const int trials = 1000;

    for (int i = 0; i < trials; ++i)
    {
        Qubit temp_qubit = qubit;
        int result = temp_qubit.measure();
        if (result == 0)
            ++zero_count;
        else if (result == 1)
            ++one_count;
    }

    EXPECT_NEAR(zero_count, trials / 2, trials * 0.1);
    EXPECT_NEAR(one_count, trials / 2, trials * 0.1);
}
