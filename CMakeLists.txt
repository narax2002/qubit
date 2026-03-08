cmake_minimum_required(VERSION 3.20)
project(qubit LANGUAGES CXX)

option(QUBIT_ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer." OFF)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED Yes)
set(CMAKE_CXX_EXTENSIONS No)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRCS
	src/qubit.cpp
	src/gates/one_qubit.cpp
	src/gates/multi_qubit.cpp
	src/algorithms/bernstein_vazirani.cpp
	src/algorithms/grover.cpp
	src/algorithms/qft.cpp
	src/algorithms/shor.cpp)

add_library(${PROJECT_NAME} STATIC ${SRCS})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(
	${PROJECT_NAME}
	PUBLIC $<INSTALL_INTERFACE:include>
           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_compile_options(
	${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-Wall
	                             -Wextra -Werror>)

if(QUBIT_ENABLE_SANITIZERS)
	if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
		target_compile_options(
			${PROJECT_NAME} PUBLIC -fsanitize=address,undefined -fno-omit-frame-pointer)
		target_link_options(${PROJECT_NAME} PUBLIC -fsanitize=address,undefined)
	else()
		message(FATAL_ERROR "QUBIT_ENABLE_SANITIZERS requires GCC or Clang.")
	endif()
endif()

add_subdirectory(examples)
enable_testing()
add_subdirectory(tests)
