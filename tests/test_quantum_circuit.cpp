#include <gtest/gtest.h>
#include "quantum_circuit.h"
#include "quantum_gate.h"
#include "log_capture.h"
#include "logger.h"

TEST(QuantumCircuitTest, AddGateAndExecute)
{
    Logger::init_logging();
    QuantumCircuit circuit(1);
    LogCapture log_capture;

    circuit.add_gate([&circuit]() { QuantumGate::apply_hadamard(circuit.qubit(0)); });
    circuit.execute();

    EXPECT_NEAR(std::norm(circuit.qubit(0).get_alpha()), 0.5, 1e-6);
    EXPECT_NEAR(std::norm(circuit.qubit(0).get_beta()), 0.5, 1e-6);
}

TEST(QuantumCircuitTest, MultipleGates)
{
    Logger::init_logging();
    QuantumCircuit circuit(1);
    LogCapture log_capture;

    circuit.add_gate([&circuit]() { QuantumGate::apply_hadamard(circuit.qubit(0)); });
    circuit.add_gate([&circuit]() { QuantumGate::apply_pauli_x(circuit.qubit(0)); });
    circuit.execute();

    EXPECT_NEAR(std::norm(circuit.qubit(0).get_alpha()), 0.5, 1e-6);
    EXPECT_NEAR(std::norm(circuit.qubit(0).get_beta()), 0.5, 1e-6);
}

TEST(QuantumCircuitTest, ControlNotGate)
{
    Logger::init_logging();
    QuantumCircuit circuit(2);
    LogCapture log_capture;

    circuit.qubit(0).set_state({0, 0}, {1, 0});
    circuit.add_gate([&circuit]() { QuantumGate::apply_cnot(circuit.qubit(0), circuit.qubit(1)); });
    circuit.execute();

    EXPECT_EQ(circuit.qubit(1).get_alpha(), std::complex<double>(0, 0));
    EXPECT_EQ(circuit.qubit(1).get_beta(), std::complex<double>(1, 0));
}
