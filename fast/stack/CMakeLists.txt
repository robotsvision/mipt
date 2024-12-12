cmake_minimum_required(VERSION 3.10)
project(Stack)

add_library(stack STATIC
    "src/stack.c"
)

target_include_directories(stack PUBLIC
    "include/"
)
