cmake_minimum_required(VERSION 3.10)
project(Akinator)

add_executable(akinator
    "src/main.c"
    "src/utils/graphviz.c"
    "src/utils/graphviz_calls.c"
)

target_include_directories(akinator PUBLIC
    "include/"
)
