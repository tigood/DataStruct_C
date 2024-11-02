cmake_minimum_required(VERSION 3.29)
project(hash_quad C)

set(CMAKE_C_STANDARD 11)

add_executable(hash_quad main.c
        hash_quad.h)
