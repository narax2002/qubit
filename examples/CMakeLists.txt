add_executable(bernstein_vazirani bernstein_vazirani.cpp)
target_link_libraries(bernstein_vazirani PUBLIC qubit)

add_executable(grover grover.cpp)
target_link_libraries(grover PUBLIC qubit)
