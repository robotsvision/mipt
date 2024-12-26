cmake_minimum_required(VERSION 3.10)
project(list)

include_directories(include/)
add_library(list STATIC
    "src/list.c"
)


