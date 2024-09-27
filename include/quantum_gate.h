#pragma once

#include "quantum_circuit.h"
#include "qubit.h"

class QuantumGate
{
public:
    static void apply_pauli_x(Qubit& qubit);
    static void apply_pauli_y(Qubit& qubit);
    static void apply_pauli_z(Qubit& qubit);
    static void apply_hadamard(Qubit& qubit);
    static void apply_phase_shift(Qubit& qubit, double theta);
    static void apply_t_gate(Qubit& qubit);

    static void apply_cnot(Qubit& control, Qubit& target);
    static void apply_cz(Qubit& control, Qubit& target);
    static void apply_swap(Qubit& qubit1, Qubit& qubit2);

    static void apply_controlled_phase_shift(Qubit& control, Qubit& target, double theta);

    static void apply_qft(QuantumCircuit& circuit, int start_idx, int end_idx);
};
