cmake_minimum_required(VERSION 3.16)
project(Qubit)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

set(SRCS
	src/qubit_operator.cpp
	src/one_qubit_gates.cpp
	src/multi_qubit_gates.cpp
	src/qubit_Bernstein_Vazirani.cpp
	src/qubit_Grover.cpp
	src/qubit_QFT.cpp
	src/qubit_Shor.cpp)

add_library(Qubit SHARED ${SRCS})
target_include_directories(
	${PROJECT_NAME}
	PUBLIC $<INSTALL_INTERFACE:include>
           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_compile_options(
	${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-Wall
                             -Wextra -Werror>)

add_executable(Sample sample.cpp)
target_link_libraries(Sample PUBLIC Qubit)
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
	target_link_libraries(Sample PRIVATE OpenMP::OpenMP_CXX)
endif()
