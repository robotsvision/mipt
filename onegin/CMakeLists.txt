cmake_minimum_required(VERSION 3.10)
project(Onegin)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic -m64")
set(CMAKE_C_FLAGS_DEBUG "-D DEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_EXE_LINKER_FLAGS "-m64")

include_directories(include/)
file(GLOB_RECURSE ONEGIN_SRC "src/*.c")
add_executable(onegin ${ONEGIN_SRC})

set(ASM_COMPILER fasm)
file(GLOB_RECURSE ASM_SRC "asm/x86_64/${CMAKE_SYSTEM_NAME}/*.S")

set(ASM_OBJECTS "")
foreach(ASM_FILE ${ASM_SRC})

    get_filename_component(ASM_FILENAME ${ASM_FILE} NAME_WE)
    set(ASM_OUTPUT "${CMAKE_BINARY_DIR}/${ASM_FILENAME}.obj")

    add_custom_command(
        OUTPUT ${ASM_OUTPUT}
        COMMAND ${ASM_COMPILER} ${ASM_FILE} ${ASM_OUTPUT}
        DEPENDS ${ASM_FILE}
        COMMENT "Compiling ${ASM_FILE} to ${ASM_OUTPUT}"
    )
    list(APPEND ASM_OBJECTS ${ASM_OUTPUT})
endforeach()

# Добавляем все собранные объекты как зависимости
add_custom_target(Generate_assembly ALL DEPENDS ${ASM_OBJECTS})
add_dependencies(onegin Generate_assembly)

# Связываем с собранными объектами
target_link_libraries(onegin PRIVATE ${ASM_OBJECTS})
