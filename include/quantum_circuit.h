#pragma once

#include "qubit.h"
#include <vector>
#include <functional>

class QuantumCircuit
{
public:
    QuantumCircuit(int num_qubits);

    // Добавление гейта в цепь
    void add_gate(const std::function<void()>& gate_operation);

    // Выполнение цепи
    void execute();

    // Доступ к кубитам
    Qubit& qubit(int index);

    // Отображение состояния цепи
    void display_state() const;

    void initialize_superposition();

    void apply_mod_exp_operator(int a, int N, int index);

    void apply_qft(int start_idx, int end_idx);

    std::vector<int> measure_all();

private:
    std::vector<Qubit> qubits_;
    std::vector<std::function<void()>> gates_;
};
