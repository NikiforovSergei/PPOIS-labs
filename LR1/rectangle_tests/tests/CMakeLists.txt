include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(
        run_rectangle_tests
        rectangle_tests.cpp
)

target_link_libraries(run_rectangle_tests gtest gtest_main)
target_link_libraries(run_rectangle_tests rectangle_lib)