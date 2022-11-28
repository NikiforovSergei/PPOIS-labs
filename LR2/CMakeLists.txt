cmake_minimum_required(VERSION 2.8...3.22)
project(BBANK)

set(CMAKE_CXX_STANDARD 23)
set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic ${CMAKE_CXX_STANDARD_LIBRARIES}")
configure_file(BANKS.h ATMScreens.h)
aux_source_directory(${SOURCES_DIR} SOURCES)
include_directories(${SOURCES_DIR})

add_executable(BBANK main.cpp BANKS.cpp BANKS.h ATMScreens.cpp ATMScreens.h)
