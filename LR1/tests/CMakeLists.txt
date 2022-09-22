find_package(GTest REQUIRED)

add_executable(polynominal_test polynominal_test.cpp)

target_link_libraries(polynominal_test
 PRIVATE
  GTest::GTest
  polynominal)

add_test(polynominal_gtest polynominal_test)
