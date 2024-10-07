cmake_minimum_required(VERSION 3.10)
project(Onegin)

set(CMAKE_C_FLAGS "--pedantic")

add_executable(onegin
    src/util/files.c

    src/onegin.c
    src/main.c
)
target_include_directories(onegin PRIVATE "include/")
