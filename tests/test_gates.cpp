#include <gtest/gtest.h>
#include "quantum_gate.h"
#include "qubit.h"

TEST(QuantumGateTest, ApplyPauliX)
{
    Qubit qubit;
    qubit = QuantumGate::apply_pauli_x(qubit);
    EXPECT_EQ(qubit.measure(), 1);
}

TEST(QuantumGateTest, ApplyHadamard)
{
    Qubit qubit;
    qubit = QuantumGate::apply_hadamard(qubit);
    auto alpha = qubit.get_alpha();
    auto beta = qubit.get_beta();
    EXPECT_NEAR(std::abs(alpha), std::abs(beta), 1e-6);
}
