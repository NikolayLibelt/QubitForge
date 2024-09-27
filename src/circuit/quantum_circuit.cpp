#include "quantum_circuit.h"
#include "quantum_gate.h"
#include <iostream>
#include <vector>

QuantumCircuit::QuantumCircuit(int num_qubits)
{
    qubits.reserve(num_qubits);
    for (int i = 0; i < num_qubits; ++i)
    {
        qubits.emplace_back(); // Все кубиты инициализируются в состоянии |0>
    }
}

void QuantumCircuit::apply_gate_to_qubit(const QuantumGate::Matrix& gate, int qubit_index)
{
    if (qubit_index < 0 || static_cast<size_t>(qubit_index) >= qubits.size())
    {
        std::cerr << "Ошибка: Неверный индекс кубита." << std::endl;
        return;
    }

    Qubit& qubit = qubits[qubit_index];

    // Применяем однокубитный гейт к состоянию кубита
    std::complex<double> new_alpha = gate[0][0] * qubit.get_alpha() + gate[0][1] * qubit.get_beta();
    std::complex<double> new_beta = gate[1][0] * qubit.get_alpha() + gate[1][1] * qubit.get_beta();

    qubit = Qubit(new_alpha, new_beta);
}

void QuantumCircuit::apply_cnot(int control_index, int target_index)
{
    if (control_index < 0 || static_cast<size_t>(control_index) >= qubits.size() || target_index < 0 ||
        static_cast<size_t>(target_index) >= qubits.size())
    {
        std::cerr << "Ошибка: Неверные индексы кубитов." << std::endl;
        return;
    }

    auto result = QuantumGate::apply_cnot(qubits[control_index], qubits[target_index]);

    qubits[control_index] = Qubit(result[0] + result[1], result[2] + result[3]);
    qubits[target_index] = Qubit(result[0] + result[2], result[1] + result[3]);
}

void QuantumCircuit::apply_swap(int q1_index, int q2_index)
{
    if (q1_index < 0 || static_cast<size_t>(q1_index) >= qubits.size() || q2_index < 0 ||
        static_cast<size_t>(q2_index) >= qubits.size())
    {
        std::cerr << "Ошибка: Неверные индексы кубитов." << std::endl;
        return;
    }

    auto result = QuantumGate::apply_swap(qubits[q1_index], qubits[q2_index]);

    qubits[q1_index] = Qubit(result[0] + result[1], result[2] + result[3]);
    qubits[q2_index] = Qubit(result[0] + result[2], result[1] + result[3]);
}

void QuantumCircuit::display_circuit_state() const
{
    for (size_t i = 0; i < qubits.size(); ++i)
    {
        std::cout << "Кубит " << i << ": ";
        qubits[i].display_state();
    }
}

Qubit& QuantumCircuit::get_qubit(int index)
{
    return qubits[index];
}