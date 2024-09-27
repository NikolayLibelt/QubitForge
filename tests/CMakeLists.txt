cmake_minimum_required(VERSION 3.10)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(${CMAKE_SOURCE_DIR}/deps/googletest ${CMAKE_BINARY_DIR}/googletest_build)

add_executable(test_circuit test_circuit.cpp)
add_executable(test_gates test_gates.cpp)
add_executable(test_qubit test_qubit.cpp)
add_executable(test_simulator test_simulator.cpp)
add_executable(test_algorithms test_algorithms.cpp)

target_link_libraries(test_circuit gtest gtest_main qubitforge_lib)
target_link_libraries(test_gates gtest gtest_main qubitforge_lib)
target_link_libraries(test_qubit gtest gtest_main qubitforge_lib)
target_link_libraries(test_simulator gtest gtest_main qubitforge_lib)
target_link_libraries(test_algorithms gtest gtest_main qubitforge_lib)

enable_testing()

add_test(NAME test_circuit COMMAND test_circuit)
add_test(NAME test_gates COMMAND test_gates)
add_test(NAME test_qubit COMMAND test_qubit)
add_test(NAME test_simulator COMMAND test_simulator)
add_test(NAME test_algorithms COMMAND test_algorithms)
