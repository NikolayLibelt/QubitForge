#include "quantum_gate.h"
#include <cmath>

Qubit QuantumGate::apply_pauli_x(const Qubit& qubit)
{
    return {qubit.get_beta(), qubit.get_alpha()};
}

Qubit QuantumGate::apply_pauli_y(const Qubit& qubit)
{
    return {std::complex<double>(0, -1) * qubit.get_beta(), std::complex<double>(0, 1) * qubit.get_alpha()};
}

Qubit QuantumGate::apply_pauli_z(const Qubit& qubit)
{
    return {qubit.get_alpha(), -qubit.get_beta()};
}

Qubit QuantumGate::apply_hadamard(const Qubit& qubit)
{
    const double sqrt2_inv = 1.0 / std::sqrt(2);
    std::complex<double> new_alpha = sqrt2_inv * (qubit.get_alpha() + qubit.get_beta());
    std::complex<double> new_beta = sqrt2_inv * (qubit.get_alpha() - qubit.get_beta());
    return {new_alpha, new_beta};
}

Qubit QuantumGate::apply_phase_shift(const Qubit& qubit, double phase)
{
    std::complex<double> phase_factor = std::polar(1.0, phase);
    return {qubit.get_alpha(), qubit.get_beta() * phase_factor};
}

Qubit QuantumGate::apply_t_gate(const Qubit& qubit)
{
    const double pi_over_4 = M_PI / 4;
    return apply_phase_shift(qubit, pi_over_4);
}

std::vector<std::complex<double>> QuantumGate::apply_cnot(Qubit control, Qubit target)
{
    auto state = Qubit::entangle(control, target);

    if (control.measure() == 1)
    {
        std::swap(state[2], state[3]);
    }

    return state;
}

std::vector<std::complex<double>> QuantumGate::apply_cz(Qubit control, Qubit target)
{
    auto state = Qubit::entangle(control, target);

    if (control.measure() == 1)
    {
        state[3] = -state[3];
    }

    return state;
}

std::vector<std::complex<double>> QuantumGate::apply_swap(Qubit q1, Qubit q2)
{
    auto state = Qubit::entangle(q1, q2);

    std::swap(state[1], state[2]);

    return state;
}
