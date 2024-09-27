#include "qubit.h"
#include "logger.h"
#include <iostream>
#include <random>

Qubit::Qubit() : alpha_(1), beta_(0)
{
    Logger::log_info("Создан кубит с состоянием |0>");
}

Qubit::Qubit(const std::complex<double>& alpha, const std::complex<double>& beta) : alpha_(alpha), beta_(beta)
{
    _normalize();
    Logger::log_info("Создан кубит с пользовательским состоянием");
}

std::complex<double> Qubit::get_alpha() const
{
    Logger::log_debug("Получено значение alpha: " + std::to_string(alpha_.real()) + " + " +
                      std::to_string(alpha_.imag()) + "i");
    return alpha_;
}

std::complex<double> Qubit::get_beta() const
{
    Logger::log_debug("Получено значение beta: " + std::to_string(beta_.real()) + " + " + std::to_string(beta_.imag()) +
                      "i");
    return beta_;
}

void Qubit::set_state(const std::complex<double>& alpha, const std::complex<double>& beta)
{
    Logger::log_info("Установка нового состояния кубита");
    alpha_ = alpha;
    beta_ = beta;
    _normalize();
    Logger::log_debug("Новое состояние: alpha = " + std::to_string(alpha_.real()) + " + " +
                      std::to_string(alpha_.imag()) + "i, beta = " + std::to_string(beta_.real()) + " + " +
                      std::to_string(beta_.imag()) + "i");
}

void Qubit::_normalize()
{
    double norm = std::norm(alpha_) + std::norm(beta_);
    if (norm > 0)
    {
        alpha_ /= std::sqrt(norm);
        beta_ /= std::sqrt(norm);
    }
    Logger::log_debug("Состояние нормализовано: alpha = " + std::to_string(alpha_.real()) + " + " +
                      std::to_string(alpha_.imag()) + "i, beta = " + std::to_string(beta_.real()) + " + " +
                      std::to_string(beta_.imag()) + "i");
}

void Qubit::display_state() const
{
    Logger::log_info("Отображение состояния кубита");
    std::cout << "(" << alpha_ << ")|0> + (" << beta_ << ")|1>" << std::endl;
}

int Qubit::measure()
{
    Logger::log_info("Измерение кубита");
    double prob_zero = std::norm(alpha_);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution d(prob_zero);
    int result = d(gen) ? 0 : 1;

    if (result == 0)
    {
        alpha_ = 1;
        beta_ = 0;
        Logger::log_info("Измерение: результат 0, кубит приведен к состоянию |0>");
    }
    else
    {
        alpha_ = 0;
        beta_ = 1;
        Logger::log_info("Измерение: результат 1, кубит приведен к состоянию |1>");
    }

    return result;
}
