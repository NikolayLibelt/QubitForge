#include "deutsch_jozsa.h"
#include "quantum_circuit.h"
#include "quantum_gate.h"
#include "logger.h"

void DeutschJozsaAlgorithm::run(const std::function<int(int)>& oracle, int num_qubits)
{
    Logger::log_info("Запуск алгоритма Дойча-Йожи с количеством кубитов: " + std::to_string(num_qubits));
    QuantumCircuit circuit(num_qubits + 1);

    // Инициализация последнего кубита в состоянии |1>
    circuit.qubit(num_qubits).set_state(0, 1);

    // Применение Адамара ко всем кубитам
    for (int i = 0; i <= num_qubits; ++i)
    {
        circuit.add_gate([&circuit, i]() { QuantumGate::apply_hadamard(circuit.qubit(i)); });
    }

    // Применение оракула
    circuit.add_gate(
        [&]()
        {
            for (int i = 0; i < num_qubits; ++i)
            {
                int oracle_result = oracle(i);
                if (oracle_result)
                {
                    QuantumGate::apply_cnot(circuit.qubit(i), circuit.qubit(num_qubits));
                }
            }
        });

    // Применение Адамара к первым n кубитам
    for (int i = 0; i < num_qubits; ++i)
    {
        circuit.add_gate([&circuit, i]() { QuantumGate::apply_hadamard(circuit.qubit(i)); });
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

    // Проверка сбалансированности или константности функции
    bool is_constant = std::all_of(results.begin(), results.end(), [](int bit) { return bit == 0; });
    if (is_constant)
    {
        Logger::log_info("Функция константная.");
    }
    else
    {
        Logger::log_info("Функция сбалансированная.");
    }
}