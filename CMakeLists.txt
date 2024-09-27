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

set(SOURCES
    src/main.cpp
    src/algorithms/deutsch_jozsa.cpp
    src/algorithms/grover.cpp
    src/algorithms/shor.cpp
    src/algorithms/quantum_algorithm.cpp
    src/circuit/quantum_circuit.cpp
    src/gates/quantum_gate.cpp
    src/register/quantum_register.cpp
    src/utils/matrix.cpp
    src/utils/utils.cpp
)

add_executable(QubitForge ${SOURCES})

target_include_directories(QubitForge PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_compile_options(QubitForge PRIVATE ${COMMON_COMPILE_OPTIONS})

# Подключение дополнительных библиотек, если они появятся в будущем
# target_link_libraries(QubitForge PRIVATE <library>)

enable_testing()
add_subdirectory(tests)

target_include_directories(QubitForgeTests PRIVATE ${PROJECT_SOURCE_DIR}/include)