#include <gtest/gtest.h>
#include "quantum_circuit.h"
#include "quantum_gate.h"

TEST(QuantumCircuitTest, TestInitialState)
{
    QuantumCircuit circuit(1);
    testing::internal::CaptureStdout();
    circuit.display_circuit_state();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("|0>") != std::string::npos);
}

TEST(QuantumCircuitTest, TestApplyHadamardGate)
{
    QuantumCircuit circuit(1);
    QuantumGate::Matrix hadamard = {{1 / std::sqrt(2), 1 / std::sqrt(2)}, {1 / std::sqrt(2), -1 / std::sqrt(2)}};
    circuit.apply_gate_to_qubit(hadamard, 0);

    Qubit qubit = circuit.get_qubit(0);
    std::complex<double> alpha = qubit.get_alpha();
    std::complex<double> beta = qubit.get_beta();

    EXPECT_NEAR(std::abs(alpha), 1.0 / std::sqrt(2), 1e-6);
    EXPECT_NEAR(std::abs(beta), 1.0 / std::sqrt(2), 1e-6);
}
