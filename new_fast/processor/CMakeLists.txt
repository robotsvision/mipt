cmake_minimum_required(VERSION 3.10)
project(Processor)

set(CMAKE_C_FLAGS -fdiagnostics-color=always)

set(PROCESSOR_GENERAL_FLAGS "-Wall -Wextra -Wpedantic")

set(CMAKE_CXX_FLAGS_DEBUG_INIT ${PROCESSOR_GENERAL_FLAGS})
set(CMAKE_CXX_FLAGS_RELEASE_INIT ${PROCESSOR_GENERAL_FLAGS})

# -------------------------------------------------------

add_library(disassembler STATIC
    "${CMAKE_CURRENT_SOURCE_DIR}/disassembler/src/disassembler.c"
)

target_include_directories(disassembler PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/disassembler/include/"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/"
)

# -------------------------------------------------------

# -------------------------------------------------------
