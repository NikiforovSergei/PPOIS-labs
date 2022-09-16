cmake_minimum_required(VERSION 3.0.0)
project(Normal_matrix VERSION 0.1.0)


add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest"
    "googletest"
)

add_executable(
    main
    src/main.cpp
)

add_executable(
    mytest
    tests/setTest.cpp
    tests/subTest.cpp
    tests/resizeTest.cpp
    tests/mathOperatorsTest.cpp
    tests/determinantTest.cpp
    tests/extraFunc.cpp
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

target_include_directories(
    mytest PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(
    mytest PRIVATE
    gtest gtest_main
)
