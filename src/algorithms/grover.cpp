#include "grover.h"
#include "quantum_circuit.h"
#include "quantum_gate.h"
#include "logger.h"
#include <cmath>

void GroverAlgorithm::run(int num_qubits, int target_state)
{
    Logger::log_info("Запуск алгоритма Гровера с " + std::to_string(num_qubits) + " кубитами и целевым состоянием " +
                     std::to_string(target_state));

    QuantumCircuit circuit(num_qubits);

    // Применение Адамара ко всем кубитам
    for (int i = 0; i < num_qubits; ++i)
    {
        circuit.add_gate([&circuit, i]() { QuantumGate::apply_hadamard(circuit.qubit(i)); });
    }

    // Оракул
    circuit.add_gate(
        [&circuit, target_state, num_qubits]()
        {
            bool match = true;
            for (int j = 0; j < num_qubits; ++j)
            {
                if (circuit.qubit(j).measure() != ((target_state >> j) & 1))
                {
                    match = false;
                    break;
                }
            }

            if (match)
            {
                for (int j = 0; j < num_qubits; ++j)
                {
                    QuantumGate::apply_pauli_z(circuit.qubit(j));
                }
            }
        });

    // Применение диффузионного оператора
    for (int i = 0; i < num_qubits; ++i)
    {
        circuit.add_gate(
            [&circuit, i]()
            {
                QuantumGate::apply_hadamard(circuit.qubit(i));
                QuantumGate::apply_pauli_z(circuit.qubit(i));
                QuantumGate::apply_hadamard(circuit.qubit(i));
            });
    }

    // Выполнение цепи
    circuit.execute();

    // Измерение результатов
    std::vector<int> results;
    results.reserve(num_qubits);
    for (int i = 0; i < num_qubits; ++i)
    {
        results.push_back(circuit.qubit(i).measure());
    }

    // Определение найденного состояния
    int measured_state = 0;
    for (int i = 0; i < num_qubits; ++i)
    {
        measured_state |= (results[i] << i);
    }

    Logger::log_info("Найденное состояние: " + std::to_string(measured_state));
}