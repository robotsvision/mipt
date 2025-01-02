cmake_minimum_required(VERSION 3.10)
project(Stack)

add_library(stack SHARED
    "src/stack.c"
    "src/stack.cpp"
    "src/system_info.c"
)

target_include_directories(stack PUBLIC
    "include/"
)
