cmake_minimum_required(VERSION 3.16)
project(qubit LANGUAGES CXX)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED Yes)
set(CMAKE_CXX_EXTENSIONS No)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRCS
	src/qubit_operator.cpp
	src/one_qubit_gates.cpp
	src/multi_qubit_gates.cpp
	src/qubit_Bernstein_Vazirani.cpp
	src/qubit_Grover.cpp
	src/qubit_qft.cpp
	src/qubit_Shor.cpp)

add_library(${PROJECT_NAME} STATIC ${SRCS})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(
	${PROJECT_NAME}
	PUBLIC $<INSTALL_INTERFACE:include>
           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_compile_options(
	${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-Wall
	                             -Wextra -Werror>)

add_subdirectory(examples)
enable_testing()
add_subdirectory(tests)
