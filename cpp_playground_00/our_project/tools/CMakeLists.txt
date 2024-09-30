if (BUILD_TESTING)
    message(STATUS "BUILD_TESTING is on")
    add_executable(tools_test tools_test.cpp)
    target_link_libraries(tools_test PRIVATE GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(tools_test)
endif()
 
add_library(tools tools.cpp)
target_link_libraries(tools PUBLIC cxx_setup)