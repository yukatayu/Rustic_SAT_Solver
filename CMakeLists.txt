cmake_minimum_required(VERSION 2.6)
project(cpp_rustic_sat CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(rustic_sat solver.cpp)

target_include_directories(rustic_sat
	PUBLIC ${PROJECT_SOURCE_DIR}/
)

