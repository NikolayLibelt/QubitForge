#include "deutsch_jozsa.h"
#include "grover.h"
#include "logger.h"
#include "shor.h"
#include <iostream>

int main()
{
    Logger::init_logging();
    Logger::log_info("Программа запущена");

    int choice = 0;
    int number = 0;
    std::cout << "Выберите алгоритм:\n1. Дойча–Йожи\n2. Гровера\n3. Шора\n";
    std::cin >> choice;
    Logger::log_info("Выбор пользователя: " + std::to_string(choice));

    switch (choice)
    {
    case 1:
        Logger::log_info("Запуск алгоритма Дойча-Йожи");
        DeutschJozsaAlgorithm::run([](int x) { return x % 2; }, 2);
        break;
    case 2:
        Logger::log_info("Запуск алгоритма Гровера");
        GroverAlgorithm::run(2, 3);
        break;
    case 3:
        std::cout << "Введите число для факторизации: ";
        std::cin >> number;
        Logger::log_info("Запуск алгоритма Шора для числа: " + std::to_string(number));
        ShorAlgorithm::run(number);
        break;
    default:
        Logger::log_error("Неверный выбор: " + std::to_string(choice));
        std::cout << "Неверный выбор." << std::endl;
    }

    Logger::log_info("Программа завершена");
    return 0;
}