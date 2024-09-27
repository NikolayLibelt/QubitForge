#include "quantum_register.h"
#include "logger.h"
#include <iostream>

QuantumRegister::QuantumRegister(int num_qubits)
{
    qubits_.resize(num_qubits);
    Logger::log_info("Создан квантовый регистр на " + std::to_string(num_qubits) + " кубитов");
}

Qubit& QuantumRegister::qubit(int index)
{
    Logger::log_debug("Доступ к кубиту с индексом " + std::to_string(index));
    return qubits_[index];
}

std::vector<int> QuantumRegister::measure_all()
{
    Logger::log_info("Измерение всех кубитов регистра");
    std::vector<int> results;
    results.reserve(qubits_.size());
    for (auto& qubit : qubits_)
    {
        results.push_back(qubit.measure());
    }
    Logger::log_info("Результаты измерений: " + std::to_string(results.size()) + " кубитов измерены");
    return results;
}

void QuantumRegister::display_state() const
{
    Logger::log_info("Отображение состояния квантового регистра");
    for (size_t i = 0; i < qubits_.size(); ++i)
    {
        std::cout << "Кубит " << i << ": ";
        qubits_[i].display_state();
    }
}
