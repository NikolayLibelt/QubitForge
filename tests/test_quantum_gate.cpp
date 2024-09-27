#include <gtest/gtest.h>
#include "quantum_gate.h"
#include "log_capture.h"
#include "logger.h"

TEST(QuantumGateTest, PauliXGate)
{
    Logger::init_logging();
    LogCapture log_capture;

    Qubit qubit;
    QuantumGate::apply_pauli_x(qubit);

    EXPECT_EQ(qubit.get_alpha(), std::complex<double>(0, 0));
    EXPECT_EQ(qubit.get_beta(), std::complex<double>(1, 0));
}

TEST(QuantumGateTest, PauliYGate)
{
    Logger::init_logging();
    LogCapture log_capture;

    Qubit qubit({1, 0}, {0, 0});
    QuantumGate::apply_pauli_y(qubit);

    EXPECT_EQ(qubit.get_alpha(), std::complex<double>(0, 0));
    EXPECT_EQ(qubit.get_beta(), std::complex<double>(0, 1));
}

TEST(QuantumGateTest, PauliZGate)
{
    Logger::init_logging();
    LogCapture log_capture;

    Qubit qubit({1, 0}, {0, 0});
    QuantumGate::apply_pauli_z(qubit);

    EXPECT_EQ(qubit.get_alpha(), std::complex<double>(1, 0));
    EXPECT_EQ(qubit.get_beta(), std::complex<double>(0, 0));
}

TEST(QuantumGateTest, HadamardGate)
{
    Logger::init_logging();
    LogCapture log_capture;

    Qubit qubit({1, 0}, {0, 0});
    QuantumGate::apply_hadamard(qubit);

    EXPECT_NEAR(std::norm(qubit.get_alpha()), 0.5, 1e-6);
    EXPECT_NEAR(std::norm(qubit.get_beta()), 0.5, 1e-6);
}

TEST(QuantumGateTest, PhaseShiftGate)
{
    Logger::init_logging();
    LogCapture log_capture;

    Qubit qubit({1 / std::sqrt(2), 0}, {1 / std::sqrt(2), 0});
    QuantumGate::apply_phase_shift(qubit, M_PI);

    EXPECT_NEAR(std::real(qubit.get_beta()), -1 / std::sqrt(2), 1e-6);
}

TEST(QuantumGateTest, TGate)
{
    Logger::init_logging();
    LogCapture log_capture;

    Qubit qubit({1, 0}, {0, 0});
    QuantumGate::apply_t_gate(qubit);

    EXPECT_EQ(qubit.get_alpha(), std::complex<double>(1, 0));
    EXPECT_EQ(qubit.get_beta(), std::complex<double>(0, 0));
}

TEST(QuantumGateTest, CNOTGate)
{
    Logger::init_logging();
    LogCapture log_capture;

    Qubit control({0, 0}, {1, 0});
    Qubit target({1, 0}, {0, 0});
    QuantumGate::apply_cnot(control, target);

    EXPECT_EQ(target.get_alpha(), std::complex<double>(0, 0));
    EXPECT_EQ(target.get_beta(), std::complex<double>(1, 0));
}

TEST(QuantumGateTest, CZGate)
{
    Logger::init_logging();
    LogCapture log_capture;

    Qubit control({0, 0}, {1, 0});
    Qubit target({1, 0}, {0, 0});
    QuantumGate::apply_cz(control, target);

    EXPECT_EQ(target.get_alpha(), std::complex<double>(1, 0));
    EXPECT_EQ(target.get_beta(), std::complex<double>(0, 0));
}

TEST(QuantumGateTest, SwapGate)
{
    Logger::init_logging();
    LogCapture log_capture;

    Qubit qubit1({1, 0}, {0, 0});
    Qubit qubit2({0, 0}, {1, 0});
    QuantumGate::apply_swap(qubit1, qubit2);

    EXPECT_EQ(qubit1.get_alpha(), std::complex<double>(0, 0));
    EXPECT_EQ(qubit1.get_beta(), std::complex<double>(1, 0));
    EXPECT_EQ(qubit2.get_alpha(), std::complex<double>(1, 0));
    EXPECT_EQ(qubit2.get_beta(), std::complex<double>(0, 0));
}
