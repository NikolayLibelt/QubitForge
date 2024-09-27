#include <gtest/gtest.h>
#include "quantum_circuit.h"
#include "quantum_gate.h"
#include "log_capture.h"
#include "logger.h"

TEST(IntegrationTest, BellState)
{
    Logger::init_logging();
    LogCapture log_capture;

    QuantumCircuit circuit(2);

    circuit.add_gate([&circuit]() { QuantumGate::apply_hadamard(circuit.qubit(0)); });

    circuit.add_gate([&circuit]() { QuantumGate::apply_cnot(circuit.qubit(0), circuit.qubit(1)); });

    circuit.execute();

    std::string logs = log_capture.get_logs();
    EXPECT_TRUE(logs.find("Состояние после схемы Белла") != std::string::npos);

    EXPECT_NEAR(std::norm(circuit.qubit(0).get_alpha()), 0.5, 1e-6);
    EXPECT_NEAR(std::norm(circuit.qubit(1).get_alpha()), 0.5, 1e-6);
}
