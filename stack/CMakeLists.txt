cmake_minimum_required(VERSION 3.10)
project(Stack)


add_library(stack STATIC)
file(GLOB_RECURSE STACK_SRC_FILES "src/*c")
target_sources(stack ${STACK_SRC_FILES})