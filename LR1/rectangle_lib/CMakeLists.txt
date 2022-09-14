project(rectangle_lib)

set(HEADERS Rectangle.h)
set(SOURCES Rectangle.cpp)

add_library(rectangle_lib STATIC ${HEADERS} ${SOURCES})