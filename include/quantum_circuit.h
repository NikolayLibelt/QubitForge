#pragma once

#include "quantum_gate.h"
#include "qubit.h"
#include <vector>

class QuantumCircuit
{
private:
    std::vector<Qubit> qubits;

public:
    QuantumCircuit(int num_qubits);

    void apply_gate_to_qubit(const QuantumGate::Matrix& gate, int qubit_index);
    void apply_cnot(int control_index, int target_index);
    void apply_swap(int q1_index, int q2_index);
    Qubit& get_qubit(int index);

    void display_circuit_state() const;
};
