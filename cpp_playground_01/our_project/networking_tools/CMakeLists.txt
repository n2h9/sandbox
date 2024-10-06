if (BUILD_TESTING)
    message(STATUS "BUILD_TESTING is on")
    add_executable(
        networking_tools_test
        networking_tools.cpp
        networking_tools_test.cpp
    )

    target_link_libraries(networking_tools_test PRIVATE GTest::gtest_main cxx_setup)

    include(GoogleTest)
    gtest_discover_tests(networking_tools_test)
endif()

add_library(
    networking_tools 
    networking_tools.cpp
)
target_link_libraries(networking_tools PUBLIC cxx_setup)