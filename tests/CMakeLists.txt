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

add_executable(test_algorithms
    one_qubit_test_main.cpp
    test_algorithms.cpp)

target_link_libraries(test_algorithms PUBLIC qubit)

add_test(NAME algorithms COMMAND test_algorithms)

add_executable(test_memory_safety
    one_qubit_test_main.cpp
    test_memory_safety.cpp)

target_link_libraries(test_memory_safety PUBLIC qubit)

add_test(NAME memory_safety COMMAND test_memory_safety)
