project(matrix_lib)

set(HEADER_FILES
        Matrix.h
        )

set(SOURCE_FILES
        Matrix.cpp
        )

add_library(matrix STATIC ${SOURCE_FILES} ${HEADER_FILES})