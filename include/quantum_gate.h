#pragma once

#include <complex>
#include <vector>
#include "qubit.h"

class QuantumGate
{
public:
    using Matrix = std::vector<std::vector<std::complex<double>>>;

    static Qubit apply_pauli_x(const Qubit& qubit);
    static Qubit apply_pauli_y(const Qubit& qubit);
    static Qubit apply_pauli_z(const Qubit& qubit);
    static Qubit apply_hadamard(const Qubit& qubit);
    static Qubit apply_phase_shift(const Qubit& qubit, double phase);
    static Qubit apply_t_gate(const Qubit& qubit);

    static std::vector<std::complex<double>> apply_cnot(Qubit control, Qubit target);
    static std::vector<std::complex<double>> apply_cz(Qubit control, Qubit target);
    static std::vector<std::complex<double>> apply_swap(Qubit q1, Qubit q2);
};
