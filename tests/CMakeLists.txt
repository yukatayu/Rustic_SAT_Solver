cmake_minimum_required(VERSION 2.6)
project(cpp_rustic_sat CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(rustic_sat ../solver.cpp)

include_directories(
	PUBLIC ${PROJECT_SOURCE_DIR}/../
)

add_executable(usage usage.cpp)
enable_testing()
add_test(usage usage)
target_link_libraries (usage rustic_sat)

