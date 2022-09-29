# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(google_test)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include_directories(../Lib/include ../Lib)
# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(Google_Tests_run TestFIles/FunctionalTesting.cpp ../Lib/postMachine.h ../Lib/postMachine.cpp TestFIles/RealTests.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main)