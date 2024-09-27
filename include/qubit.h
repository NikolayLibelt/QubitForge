#pragma once

#include <cmath>
#include <complex>
#include <iostream>
#include <random>
#include <vector>

class Qubit
{
private:
    std::complex<double> _alpha;
    std::complex<double> _beta;

    static constexpr double SQRT_2 = 0.7071067811865476; // Предвычисленное значение 1 / sqrt(2)
    static constexpr double NORMALIZATION_THRESHOLD = 1e-6;

public:
    Qubit() : _alpha(1), _beta(0) {}

    Qubit(std::complex<double> a, std::complex<double> b) : _alpha(a), _beta(b)
    {
        _normalize(a, b);
    }

    Qubit(const Qubit& other) = default;

    Qubit& operator=(const Qubit& other)
    {
        if (this != &other)
        {
            _alpha = other._alpha;
            _beta = other._beta;
        }
        return *this;
    }

    Qubit(Qubit&& other) noexcept : _alpha(other._alpha), _beta(other._beta) {}

    Qubit& operator=(Qubit&& other) noexcept
    {
        if (this != &other)
        {
            _alpha = other._alpha;
            _beta = other._beta;
        }
        return *this;
    }

    ~Qubit() = default;

    void display_state() const
    {
        std::cout << "Состояние кубита: (" << _alpha << ")|0> + (" << _beta << ")|1>" << '\n';
    }

    [[nodiscard]] std::complex<double> get_alpha() const
    {
        return _alpha;
    }

    [[nodiscard]] std::complex<double> get_beta() const
    {
        return _beta;
    }

    static std::vector<std::complex<double>> entangle(const Qubit& q1, const Qubit& q2)
    {
        std::vector<std::complex<double>> state(4);

        state[0] = q1._alpha * q2._alpha;
        state[1] = q1._alpha * q2._beta;
        state[2] = q1._beta * q2._alpha;
        state[3] = q1._beta * q2._beta;

        return state;
    }

    static std::vector<std::complex<double>> create_bell_state()
    {
        std::vector<std::complex<double>> state(4, 0);
        state[0] = SQRT_2;
        state[3] = SQRT_2;
        return state;
    }

    int measure()
    {
        double prob0 = std::norm(_alpha);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        double rand_num = dis(gen);

        if (rand_num < prob0)
        {
            _alpha = 1;
            _beta = 0;
            return 0;
        }
        else
        {
            _alpha = 0;
            _beta = 1;
            return 1;
        }
    }

private:
    void _normalize(std::complex<double>& a, std::complex<double>& b)
    {
        double norm = std::norm(a) + std::norm(b);
        if (std::abs(norm - 1.0) > NORMALIZATION_THRESHOLD)
        {
            a /= std::sqrt(norm);
            b /= std::sqrt(norm);
        }
    }
};
