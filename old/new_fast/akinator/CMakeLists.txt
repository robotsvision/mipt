cmake_minimum_required(VERSION 3.10)
project(Akinator)

set(CMAKE_C_FLAGS -fdiagnostics-color=always)

set(PROCESSOR_GENERAL_FLAGS "-Wall -Wextra -Wpedantic")

set(CMAKE_CXX_FLAGS_DEBUG_INIT ${PROCESSOR_GENERAL_FLAGS})
set(CMAKE_CXX_FLAGS_RELEASE_INIT ${PROCESSOR_GENERAL_FLAGS})

# -------------------------------------------------------

add_executable(akinator
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/akinator.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/bintree.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/resources.c"
)

target_include_directories(akinator PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include/"
)
