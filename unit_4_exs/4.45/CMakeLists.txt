cmake_minimum_required(VERSION 3.29)
project(4_45 C)

set(CMAKE_C_STANDARD 11)

add_executable(4_45 main.c
        threaded_tree.h
        threaded_tree.c)
