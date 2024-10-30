cmake_minimum_required(VERSION 3.29)
project(hash_sep C)

set(CMAKE_C_STANDARD 11)

add_executable(hash_sep main.c
        hash_sep.h
        hash_sep.c)
