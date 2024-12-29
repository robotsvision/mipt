cmake_minimum_required(VERSION 3.10)
project(StackTests)

add_executable(run_tests
    "main.cpp"
)

add_library(stack SHARED
    "../"
    "../build/"
)

# link_libraries(run_tests stack)