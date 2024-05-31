cmake_minimum_required(VERSION 3.20)
project(functional_cpp_test)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
	functional_cpp_test.cpp
)

target_include_directories(${PROJECT_NAME}
		PRIVATE ${CMAKE_SOURCE_DIR}/src/include
)
