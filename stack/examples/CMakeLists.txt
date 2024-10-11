cmake_minimum_required(VERSION 3.10)
project(StackExamples)

add_subdirectory(
    "../"
    "../../build/"
)

set(EXAMPLE_NAME "" CACHE STRING "Example to build")

if(NOT EXAMPLE_NAME)
    message(FATAL_ERROR "Please specify the EXAMPLE_NAME variable, e.g., -DEXAMPLE_NAME=push_pop.c")
endif()

get_filename_component(EXAMPLE_BASE_NAME ${EXAMPLE_NAME} NAME_WE)
get_filename_component(EXAMPLE_DIR ${EXAMPLE_NAME} EXT)
string(SUBSTRING ${EXAMPLE_DIR} 1 -1 EXAMPLE_DIR)

if (EXAMPLE_DIR STREQUAL "c" OR EXAMPLE_DIR STREQUAL "cpp")

    add_executable(${EXAMPLE_BASE_NAME}
        "${EXAMPLE_DIR}/${EXAMPLE_NAME}"
    )

    target_include_directories(${EXAMPLE_BASE_NAME} PUBLIC
        "../include"
    )
    link_libraries(${EXAMPLE_BASE_NAME} )

else()
    message(FATAL_ERROR "Invalid file format or file not exists.")
endif()


