add_executable(test_one_qubit_gates
    one_qubit_test_main.cpp
    test_one_qubit_gates.cpp)

target_link_libraries(test_one_qubit_gates PUBLIC qubit)

add_test(NAME one_qubit_gates COMMAND test_one_qubit_gates)

add_executable(test_multi_qubit_gates
    one_qubit_test_main.cpp
    test_multi_qubit_gates.cpp)

target_link_libraries(test_multi_qubit_gates PUBLIC qubit)

add_test(NAME multi_qubit_gates COMMAND test_multi_qubit_gates)
