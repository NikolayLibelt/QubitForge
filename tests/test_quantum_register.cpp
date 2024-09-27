#include <gtest/gtest.h>
#include "quantum_register.h"
#include "log_capture.h"
#include "logger.h"

TEST(QuantumRegisterTest, Initialization)
{
    Logger::init_logging();
    LogCapture log_capture;

    QuantumRegister qreg(3);
    for (int i = 0; i < 3; ++i)
    {
        EXPECT_EQ(qreg.qubit(i).get_alpha(), std::complex<double>(1, 0));
        EXPECT_EQ(qreg.qubit(i).get_beta(), std::complex<double>(0, 0));
    }
}

TEST(QuantumRegisterTest, MeasureAll)
{
    Logger::init_logging();
    LogCapture log_capture;

    QuantumRegister qreg(2);
    qreg.qubit(0).set_state({0, 0}, {1, 0});
    qreg.qubit(1).set_state({1 / std::sqrt(2), 0}, {1 / std::sqrt(2), 0});

    auto results = qreg.measure_all();

    EXPECT_EQ(results[0], 1);
    EXPECT_TRUE(results[1] == 0 || results[1] == 1);
}
