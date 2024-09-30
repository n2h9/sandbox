cmake_minimum_required(VERSION 3.28)

project(
    our_project 
    VERSION 1.0.0
    DESCRIPTION "our_project description"
    LANGUAGES CXX
)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

add_library(cxx_setup INTERFACE)
target_compile_options(cxx_setup INTERFACE -Wall -Wpedantic -Wextra)
target_compile_features(cxx_setup INTERFACE cxx_std_20)
target_include_directories(cxx_setup INTERFACE ${PROJECT_SOURCE_DIR})
message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")

include(FetchContent)

# google tests
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/releases/download/v1.15.2/googletest-1.15.2.tar.gz
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# end of googletests

# asio
FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio 
    GIT_TAG asio-1-30-2
)
# -- end of asio


FetchContent_MakeAvailable(
    googletest
    asio
)

include(CTest)

# asio support
target_include_directories(cxx_setup INTERFACE ${asio_SOURCE_DIR}/asio/include)
# // asio support

add_subdirectory(${PROJECT_NAME})
add_subdirectory(executables)