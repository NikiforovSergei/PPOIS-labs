cmake_minimum_required(VERSION 3.22)

project(Matrix)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp)
add_executable(matrix_run ${SOURCE_FILES})

include_directories(matrix_lib)

add_subdirectory(matrix_lib)
add_subdirectory(matrix_test)

target_link_libraries(matrix_run matrix)

add_custom_command(TARGET matrix_run POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/resources/ $<TARGET_FILE_DIR:matrix_run>/resources/)