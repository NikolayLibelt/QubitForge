#include "qubit.h"
#include <complex>
#include <iostream>
#include <vector>

int main()
{
    Qubit q1;
    Qubit q2(std::complex<double>(1 / std::sqrt(2)), std::complex<double>(1 / std::sqrt(2))); // Суперпозиция

    q1.display_state();
    q2.display_state();

    std::vector<std::complex<double>> entangledState = Qubit::entangle(q1, q2);

    std::cout << "Коэффициенты запутанного состояния:" << std::endl;
    std::cout << "|00>: " << entangledState[0] << std::endl;
    std::cout << "|01>: " << entangledState[1] << std::endl;
    std::cout << "|10>: " << entangledState[2] << std::endl;
    std::cout << "|11>: " << entangledState[3] << std::endl;

    std::vector<std::complex<double>> bellState = Qubit::create_bell_state();

    std::cout << "Коэффициенты состояния Белла:" << std::endl;
    std::cout << "|00>: " << bellState[0] << std::endl;
    std::cout << "|01>: " << bellState[1] << std::endl;
    std::cout << "|10>: " << bellState[2] << std::endl;
    std::cout << "|11>: " << bellState[3] << std::endl;

    return 0;
}