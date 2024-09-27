#pragma once

#include "qubit.h"
#include <vector>

class QuantumRegister
{
public:
    QuantumRegister(int num_qubits);

    // Доступ к кубитам
    Qubit& qubit(int index);

    // Измерение всех кубитов
    std::vector<int> measure_all();

    // Отображение состояния регистра
    void display_state() const;

private:
    std::vector<Qubit> qubits_;
};
