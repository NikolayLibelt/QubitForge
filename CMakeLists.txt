cmake_minimum_required(VERSION 3.10)

project(QubitForge VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(COMMON_COMPILE_OPTIONS
    -Wall
    -Wextra
    -Wpedantic
    -Werror
)

# Поиск Boost
find_package(Boost REQUIRED COMPONENTS log log_setup)

if (NOT Boost_FOUND)
    message(FATAL_ERROR "Boost libraries not found.")
endif()

# Источники для библиотеки qubitforge_lib
set(LIB_SOURCES
    src/algorithms/deutsch_jozsa.cpp
    src/algorithms/grover.cpp
    src/algorithms/shor.cpp
    src/circuit/quantum_circuit.cpp
    src/gates/quantum_gate.cpp
    src/register/quantum_register.cpp
    src/qubit/qubit.cpp
    src/logger/logger.cpp   # Логгер
)

# Создаем библиотеку qubitforge_lib
add_library(qubitforge_lib ${LIB_SOURCES})

# Подключаем заголовочные файлы
target_include_directories(qubitforge_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Устанавливаем опции компиляции
target_compile_options(qubitforge_lib PRIVATE ${COMMON_COMPILE_OPTIONS})

# Линкуем библиотеку Boost.Log
target_link_libraries(qubitforge_lib PRIVATE Boost::log Boost::log_setup)

# Исполняемый файл QubitForge
add_executable(QubitForge src/main.cpp)

# Линкуем с библиотекой qubitforge_lib
target_link_libraries(QubitForge PRIVATE qubitforge_lib)

# Подключение дополнительных библиотек, если они появятся в будущем
# target_link_libraries(QubitForge PRIVATE <library>)

# Подключаем Google Test
add_subdirectory(deps/googletest)

# Устанавливаем флаг для отключения установки googletest (необязательно)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

# Подключаем тесты
add_subdirectory(tests)
