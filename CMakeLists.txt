cmake_minimum_required(VERSION 3.26)
project(P1_Healthcare_System C)

set(CMAKE_C_STANDARD 11)

enable_testing()
set(CTEST_OUTPUT_ON_FAILURE 1)
add_subdirectory(src)
add_subdirectory(test)


