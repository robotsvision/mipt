cmake_minimum_required(VERSION 3.10)
project(DoublyLinkedListTests)

set(CMAKE_C_STANDARD 11)

add_library(dllist STATIC
    ../src/dllist.c
)

target_include_directories(dllist PUBLIC
    ../include
)
set(TEST_SOURCES
    test_create_destroy.c
    test_is_empty.c
    test_push_pop.c
    test_memory_sizes.c
    test_length.c
    test_runner.c
)

add_executable(all_tests ${TEST_SOURCES})
target_link_libraries(all_tests dllist)
