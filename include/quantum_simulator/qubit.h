#include <cmath>
#include <complex>
#include <iostream>
#include <random>
#include <vector>

class Qubit
{
private:
    std::complex<double> alpha;
    std::complex<double> beta;

    static constexpr double SQRT_2 = 0.7071067811865476; // Предвычисленное значение 1 / sqrt(2)
    static constexpr double NORMALIZATION_THRESHOLD = 1e-6;

public:
    Qubit() : alpha(1), beta(0) {}

    Qubit(std::complex<double> a, std::complex<double> b) : alpha(a), beta(b)
    {
        _normalize(a, b);
    }

    Qubit(const Qubit& other) = default;

    Qubit& operator=(const Qubit& other)
    {
        if (this != &other)
        {
            alpha = other.alpha;
            beta = other.beta;
        }
        return *this;
    }

    Qubit(Qubit&& other) noexcept : alpha(other.alpha), beta(other.beta) {}

    Qubit& operator=(Qubit&& other) noexcept
    {
        if (this != &other)
        {
            alpha = other.alpha;
            beta = other.beta;
        }
        return *this;
    }

    ~Qubit() = default;

    void display_state() const
    {
        std::cout << "Состояние кубита: (" << alpha << ")|0> + (" << beta << ")|1>" << '\n';
    }

    [[nodiscard]] std::complex<double> get_alpha() const
    {
        return alpha;
    }

    [[nodiscard]] std::complex<double> get_beta() const
    {
        return beta;
    }

    static std::vector<std::complex<double>> entangle(const Qubit& q1, const Qubit& q2)
    {
        std::vector<std::complex<double>> state(4);

        state[0] = q1.alpha * q2.alpha;
        state[1] = q1.alpha * q2.beta;
        state[2] = q1.beta * q2.alpha;
        state[3] = q1.beta * q2.beta;

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
        double prob0 = std::norm(alpha);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        double rand_num = dis(gen);

        if (rand_num < prob0)
        {
            alpha = 1;
            beta = 0;
            return 0;
        }
        else
        {
            alpha = 0;
            beta = 1;
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
