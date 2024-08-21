cmake_minimum_required(VERSION 3.10)
project(QE)

# add specific "-municode" flag
if(WIN32)
    add_compile_options(-municode)
    add_link_options(-municode)
endif()

# Add Llibs and Lingua as submodules:
add_subdirectory(external/llibs)

# Add SDL
# list(APPEND CMAKE_PREFIX_PATH  "external/")
# find_package(SDL2 REQUIRED)

# string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)

# Build QE
include_directories(include/)
file(GLOB_RECURSE QE_SRC_FILES "src/*.c")

add_executable(QE ${QE_SRC_FILES})

# Link SDL
target_link_libraries(QE PRIVATE llibs)
# include_directories(QE PRIVATE ${SDL2_INCLUDE_DIRS})
# target_link_libraries(QE PRIVATE ${SDL2_LIBRARIES})

