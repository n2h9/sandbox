cmake_minimum_required(VERSION 3.25)

project(
    c_playground_00 
    VERSION 1.0.0
    DESCRIPTION "c_playground_00 description"
    LANGUAGES C
)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

set(CMAKE_C_STANDARD 17)

add_library(c_setup INTERFACE)
target_compile_options(c_setup INTERFACE -Wall -Wpedantic -Wextra)
# target_compile_features(c_setup INTERFACE c_std_20)
target_include_directories(c_setup INTERFACE ${PROJECT_SOURCE_DIR})
message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")

add_executable(c_playground_00 main.c)
target_link_libraries(c_playground_00 c_setup)
