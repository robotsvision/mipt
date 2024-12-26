cmake_minimum_required(VERSION 3.10)
project(Akinator)

add_executable(akinator
    "src/main.c"
    "src/akinator.c"
    "src/bintree.c"
    "src/resources.c"
)

target_include_directories(akinator PUBLIC
    "include/"
)