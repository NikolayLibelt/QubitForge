#include "quantum_gate.h"
#include "logger.h"
#include <complex>
#include <cmath>

void QuantumGate::apply_pauli_x(Qubit& qubit)
{
    Logger::log_info("Применение ворот Pauli-X");
    std::complex<double> alpha = qubit.get_beta();
    std::complex<double> beta = qubit.get_alpha();
    qubit.set_state(alpha, beta);
}

void QuantumGate::apply_pauli_y(Qubit& qubit)
{
    Logger::log_info("Применение ворот Pauli-Y");
    std::complex<double> alpha = -std::complex<double>(0, 1) * qubit.get_beta();
    std::complex<double> beta = std::complex<double>(0, 1) * qubit.get_alpha();
    qubit.set_state(alpha, beta);
}

void QuantumGate::apply_pauli_z(Qubit& qubit)
{
    Logger::log_info("Применение ворот Pauli-Z");
    std::complex<double> alpha = qubit.get_alpha();
    std::complex<double> beta = -qubit.get_beta();
    qubit.set_state(alpha, beta);
}

void QuantumGate::apply_hadamard(Qubit& qubit)
{
    Logger::log_info("Применение ворот Адамара");
    std::complex<double> alpha = qubit.get_alpha();
    std::complex<double> beta = qubit.get_beta();
    std::complex<double> new_alpha = (alpha + beta) / std::sqrt(2);
    std::complex<double> new_beta = (alpha - beta) / std::sqrt(2);
    qubit.set_state(new_alpha, new_beta);
}

void QuantumGate::apply_phase_shift(Qubit& qubit, double theta)
{
    Logger::log_info("Применение фазового сдвига с углом " + std::to_string(theta));
    std::complex<double> alpha = qubit.get_alpha();
    std::complex<double> beta = qubit.get_beta() * std::polar(1.0, theta);
    qubit.set_state(alpha, beta);
}

void QuantumGate::apply_t_gate(Qubit& qubit)
{
    Logger::log_info("Применение ворот T");
    apply_phase_shift(qubit, M_PI / 4);
}

void QuantumGate::apply_cnot(Qubit& control, Qubit& target)
{
    Logger::log_info("Применение ворот CNOT");
    if (control.is_one())
    {
        QuantumGate::apply_pauli_x(target);
    }
}

void QuantumGate::apply_cz(Qubit& control, Qubit& target)
{
    Logger::log_info("Применение ворот CZ");
    if (control.measure() == 1)
    {
        QuantumGate::apply_pauli_z(target);
    }
}

void QuantumGate::apply_swap(Qubit& qubit1, Qubit& qubit2)
{
    Logger::log_info("Применение SWAP ворот");
    std::swap(qubit1, qubit2);
}

void QuantumGate::apply_controlled_phase_shift(Qubit& control, Qubit& target, double theta)
{
    if (control.measure() == 1)
    {
        apply_phase_shift(target, theta);
    }
}

void QuantumGate::apply_qft(QuantumCircuit& circuit, int start_idx, int end_idx)
{
    Logger::log_info("Применение квантового преобразования Фурье (QFT)");
    for (int i = start_idx; i < end_idx; ++i)
    {
        // Применение ворот Адамара
        apply_hadamard(circuit.qubit(i));

        // Применение контролируемых фазовых сдвигов
        for (int j = i + 1; j < end_idx; ++j)
        {
            double theta = M_PI / (1 << (j - i));
            apply_controlled_phase_shift(circuit.qubit(i), circuit.qubit(j), theta);
        }
    }

    // Переворот кубитов
    for (int i = 0; i < (end_idx - start_idx) / 2; ++i)
    {
        apply_swap(circuit.qubit(start_idx + i), circuit.qubit(end_idx - i - 1));
    }
}
