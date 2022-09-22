find_package(GTest REQUIRED)

add_executable(fraction_test fraction_test.cpp)

target_link_libraries(fraction_test
 PRIVATE
  GTest::GTest
  fraction)

add_test(fraction_gtest fraction_test)
