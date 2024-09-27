#pragma once

#include <functional>

class DeutschJozsaAlgorithm
{
public:
    static void run(const std::function<int(int)>& oracle, int num_qubits);
};
