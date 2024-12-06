cmake_minimum_required(VERSION 3.10)
project(DasmTests)

add_subdirectory( 
    "../../"
    "../../build/"
    EXCLUDE_FROM_ALL
)

add_executable(dasm_test
    test.c
)

target_include_directories(dasm_test PUBLIC
    "../../disassembler/include"
)

target_link_libraries(dasm_test PRIVATE disassembler)