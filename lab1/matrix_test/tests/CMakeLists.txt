include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(
        run_matrix_tests
        matrix_check.cpp
)

target_link_libraries(run_matrix_tests gtest gtest_main)
target_link_libraries(run_matrix_tests matrix)