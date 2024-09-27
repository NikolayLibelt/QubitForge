cmake_minimum_required(VERSION 3.10)
project(QubitForgeTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(Boost REQUIRED COMPONENTS log log_setup thread system filesystem)

enable_testing()

set(TEST_SOURCES
    test_qubit.cpp
    test_quantum_gate.cpp
    test_quantum_circuit.cpp
    test_quantum_register.cpp
    test_deutsch_jozsa.cpp
    test_grover.cpp
    test_shor.cpp
    test_integration.cpp
)

add_executable(run_tests ${TEST_SOURCES})

target_link_libraries(run_tests
    gtest
    gtest_main
    pthread
    qubitforge_lib
    ${Boost_LIBRARIES}
)

add_test(NAME RunAllTests COMMAND run_tests)
