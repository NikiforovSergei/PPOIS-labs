cmake_minimum_required(VERSION 3.22)
project(orgraph_project)

set(CMAKE_CXX_STANDARD 17)




#set(Boost_INCLUDE_DIR boost_lib/boost_1_80_0)
#set(Boost_LIBRARY_DIR boost_1_80_0/stage/lib)
#message("boost lib: ${Boost_LIBRARY_DIR}")
#message("boost inc:${Boost_INCLUDE_DIR}")
#
#find_package(Boost COMPONENTS format REQUIRED)
#if(Boost_FOUND)
#    include_directories(${Boost_INCLUDE_DIRS})
#    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
#endif()
add_executable(${PROJECT_NAME} main.cpp )

#find_package(Boost COMPONENTS format)
#if(Boost_FOUND)
#    include_directories(${Boost_INCLUDE_DIRS})
#    target_link_libraries(foo ${Boost_LIBRARIES})
#endif()


include_directories(matrix_lib orgraph_lib)

add_subdirectory(matrix_lib)
add_subdirectory(orgraph_lib)

target_link_libraries(${PROJECT_NAME} PUBLIC matrix orgraph)
#target_link_libraries(${PROJECT_NAME} )
#target_link_libraries(${PROJECT_NAME} )