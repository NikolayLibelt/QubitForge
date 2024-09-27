#include "quantum_circuit.h"
#include "logger.h"
#include "quantum_gate.h"

QuantumCircuit::QuantumCircuit(int num_qubits)
{
    qubits_.resize(num_qubits);
    Logger::log_info("Создана квантовая цепь с " + std::to_string(num_qubits) + " кубитами");
}

void QuantumCircuit::add_gate(const std::function<void()>& gate_operation)
{
    Logger::log_debug("Добавление гейта в квантовую цепь");
    gates_.push_back(gate_operation);
}

void QuantumCircuit::execute()
{
    Logger::log_info("Выполнение всех гейтов в квантовой цепи");
    for (size_t i = 0; i < gates_.size(); ++i)
    {
        Logger::log_info("Выполнение гейта " + std::to_string(i + 1));
        gates_[i]();
    }
    Logger::log_info("Выполнение цепи завершено");
}

Qubit& QuantumCircuit::qubit(int index)
{
    Logger::log_debug("Доступ к кубиту с индексом " + std::to_string(index));
    return qubits_[index];
}

void QuantumCircuit::display_state() const
{
    Logger::log_info("Отображение состояния квантовой цепи");
    for (size_t i = 0; i < qubits_.size(); ++i)
    {
        Logger::log_info("Кубит " + std::to_string(i) + " состояние: ");
        qubits_[i].display_state();
    }
}

void QuantumCircuit::initialize_superposition()
{
    for (auto& qubit : qubits_)
    {
        QuantumGate::apply_hadamard(qubit);
    }
}

void QuantumCircuit::apply_mod_exp_operator(int a, int N, int index)
{
    for (auto& qubit : qubits_)
    {
        int result = static_cast<int>(pow(a, index)) % N;
        if (result == 1)
        {
            QuantumGate::apply_cnot(qubits_[index], qubit);
        }
    }
}

void QuantumCircuit::apply_qft(int start_idx, int end_idx)
{
    QuantumGate::apply_qft(*this, start_idx, end_idx);
}

std::vector<int> QuantumCircuit::measure_all()
{
    std::vector<int> results;
    results.reserve(qubits_.size());
    for (auto& qubit : qubits_)
    {
        results.push_back(qubit.measure());
    }
    return results;
}
