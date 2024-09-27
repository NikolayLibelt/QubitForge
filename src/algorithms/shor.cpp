#include "shor.h"
#include <numeric>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "quantum_circuit.h"
#include "quantum_gate.h"
#include "logger.h"

// Выбор случайного числа a, которое взаимно просто с N
int choose_random_a(int N)
{
    srand(time(0));
    int a;
    do
    {
        a = rand() % (N - 1) + 1;
    } while (std::gcd(a, N) != 1);
    return a;
}

// Модульное экспоненцирование a^b % c
int ShorAlgorithm::_mod_exp(int base, int exponent, int modulus)
{
    int result = 1;
    base = base % modulus;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
        {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

void ShorAlgorithm::run(int N)
{
    Logger::log_info("Запуск алгоритма Шора для числа: " + std::to_string(N));

    // Шаг 1: Выбор случайного числа a
    int a = choose_random_a(N);
    Logger::log_info("Случайное число a = " + std::to_string(a));

    // Шаг 2: Проверка на наличие общих делителей
    int gcd = std::gcd(a, N);
    if (gcd != 1)
    {
        Logger::log_info("Число a = " + std::to_string(a) + " имеет делитель " + std::to_string(gcd));
        return;
    }

    // Шаг 3: Квантовая часть для поиска периода
    int period = _quantum_period_finding(a, N);
    Logger::log_info("Найден период: " + std::to_string(period));

    if (period > 0)
    {
        int factor = _calculate_factors(N, period);
        Logger::log_info("Найден делитель: " + std::to_string(factor));
    }
    else
    {
        Logger::log_info("Делители не найдены, повторяем попытку.");
    }
}

// Поиск периода через квантовую часть
int ShorAlgorithm::_quantum_period_finding(int a, int N)
{
    int num_qubits = std::ceil(std::log2(N));
    QuantumCircuit circuit(2 * num_qubits); // Создаем квантовую цепь

    Logger::log_info("Инициализация кубитов в суперпозицию.");
    circuit.initialize_superposition();

    Logger::log_info("Применение унитарного оператора для функции a^x mod N.");
    for (int i = 0; i < num_qubits; ++i)
    {
        int exponent = _mod_exp(a, i, N);
        Logger::log_debug("Унитарный оператор для a^" + std::to_string(i) + " mod " + std::to_string(N) + ": " +
                          std::to_string(exponent));
        for (int j = 0; j < num_qubits; ++j)
        {
            if (exponent & (1 << j))
            {
                QuantumGate::apply_cnot(circuit.qubit(i), circuit.qubit(num_qubits + j));
            }
        }
    }

    Logger::log_info("Применение квантового преобразования Фурье (QFT).");
    circuit.apply_qft(0, num_qubits);

    // Выполняем цепь
    circuit.execute();

    Logger::log_info("Измерение состояния кубитов.");
    std::vector<int> results = circuit.measure_all();

    int period = _classical_postprocessing(results, N, a);
    Logger::log_info("Найден период: " + std::to_string(period));

    return period;
}

// Дополнительные вспомогательные функции

// Функция для поиска делителей на основе найденного периода
int ShorAlgorithm::_calculate_factors(int N, int period)
{
    if (period % 2 != 0)
    {
        Logger::log_info("Период нечетный, повторяем.");
        return -1;
    }

    int x = _mod_exp(choose_random_a(N), period / 2, N);

    int gcd1 = std::gcd(x - 1, N);
    int gcd2 = std::gcd(x + 1, N);

    if (gcd1 != 1 && gcd1 != N)
    {
        return gcd1;
    }

    if (gcd2 != 1 && gcd2 != N)
    {
        return gcd2;
    }

    return -1; // Не удалось найти делители
}

int ShorAlgorithm::_classical_postprocessing(const std::vector<int>& result, int N, int a)
{
    // Пример классической обработки
    int period = 0;
    size_t num_bits = result.size();

    // Восстановление периода из результата измерений
    for (size_t i = 0; i < num_bits; ++i)
    {
        period |= (result[i] << i);
    }

    Logger::log_info("Постобработка: восстановленный период = " + std::to_string(period));

    if (period == 0)
    {
        Logger::log_info("Период равен 0, повторная попытка.");
        return 0;
    }

    // Попытка найти делители
    int r = period;
    if (r % 2 != 0)
    {
        Logger::log_info("Период нечётный, повторная попытка.");
        return 0;
    }

    // Проверяем значение a^r/2 mod N
    int x = _mod_exp(a, r / 2, N);
    if (x == N - 1 || x == 1)
    {
        Logger::log_info("Непригодное значение x, повторная попытка.");
        return 0;
    }

    return r;
}