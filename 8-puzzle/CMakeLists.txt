cmake_minimum_required(VERSION 3.16)
project(8_puzzle_A_star C)

set(CMAKE_C_STANDARD 11)

add_executable(8_puzzle_A_star main.c)
target_link_libraries(8_puzzle_A_star m)