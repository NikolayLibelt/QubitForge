#pragma once

#include <vector>
class ShorAlgorithm
{
public:
    // Основная функция запуска алгоритма Шора
    static void run(int N);

private:
    // Вспомогательные функции
    static int _quantum_period_finding(int a, int N); // Квантовый поиск периода
    static int _classical_gcd(int a, int b); // Нахождение НОД с помощью алгоритма Евклида
    static int _mod_exp(int base, int exponent, int modulus); // Модульное экспоненцирование
    static int _classical_mod_inverse(int a, int n); // Нахождение обратного числа по модулю
    static int _calculate_factors(int N, int period); // Вычисление делителей на основе найденного периода
    static int _classical_postprocessing(const std::vector<int>& result, int N, int a);
};
