#pragma once

#include <complex>

class Qubit
{
public:
    // Конструкторы
    Qubit();
    Qubit(const std::complex<double>& alpha, const std::complex<double>& beta);

    // Методы доступа
    [[nodiscard]] std::complex<double> get_alpha() const;
    [[nodiscard]] std::complex<double> get_beta() const;

    // Методы установки
    void set_state(const std::complex<double>& alpha, const std::complex<double>& beta);

    [[nodiscard]] std::string get_amplitudes() const
    {
        std::ostringstream oss;
        oss << "alpha = " << get_alpha() << ", beta = " << get_beta();
        return oss.str();
    }

    [[nodiscard]] bool is_one() const
    {
        // Проверяем, что амплитуда beta (состояние |1>) имеет ненулевое значение
        return std::abs(get_beta()) > 1e-6;
    }

    // Отображение состояния
    void display_state() const;

    // Измерение кубита
    int measure();

private:
    // Нормализация состояния
    void _normalize();

    std::complex<double> alpha_;
    std::complex<double> beta_;
};
