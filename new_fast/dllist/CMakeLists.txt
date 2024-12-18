cmake_minimum_required(VERSION 3.10)
project(DoubleLinkedList)

add_library(dllist STATIC
    "src/dllist.c"
)

target_include_directories(dllist PUBLIC
    "include/"
)