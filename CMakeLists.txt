cmake_minimum_required(VERSION 3.10)

# Название проекта
project(QubitForge VERSION 1.0 LANGUAGES CXX)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Включение генерации compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Основной исполняемый файл
add_executable(QubitForge src/main.cpp)

# Опции для компилятора (отладочные символы и предупреждения)
target_compile_options(QubitForge PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
)

# Папки для включения заголовков
target_include_directories(QubitForge PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Подключение дополнительных библиотек, если они появятся в будущем
# target_link_libraries(QubitForge PRIVATE <library>)

# Тесты
# enable_testing()
# add_subdirectory(tests)
