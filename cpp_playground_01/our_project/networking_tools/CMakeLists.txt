if (BUILD_TESTING)
    message(STATUS "BUILD_TESTING is on")
    add_executable(
        push_pop_queue_with_latch_test
        push_pop_queue_with_latch.cpp
        push_pop_queue_with_latch_test.cpp
    )

    target_link_libraries(push_pop_queue_with_latch_test PRIVATE GTest::gtest_main cxx_setup)

    include(GoogleTest)
    gtest_discover_tests(push_pop_queue_with_latch_test)
endif()

add_library(
    networking_tools 
    networking_tools.cpp
)
target_link_libraries(networking_tools PUBLIC cxx_setup)