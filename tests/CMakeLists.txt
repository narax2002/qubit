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

if(QUBIT_ENABLE_SANITIZERS)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(_qubit_sanitizer_env
            "ASAN_OPTIONS=detect_leaks=0"
            "UBSAN_OPTIONS=print_stacktrace=1")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(_qubit_sanitizer_env
            "ASAN_OPTIONS=detect_leaks=1"
            "UBSAN_OPTIONS=print_stacktrace=1")
    endif()

    if(DEFINED _qubit_sanitizer_env)
        set_tests_properties(
            one_qubit_gates
            multi_qubit_gates
            algorithms
            memory_safety
            PROPERTIES ENVIRONMENT "${_qubit_sanitizer_env}")
    endif()

    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set_tests_properties(
            one_qubit_gates
            multi_qubit_gates
            algorithms
            memory_safety
            PROPERTIES DISABLED TRUE)
    endif()
endif()
