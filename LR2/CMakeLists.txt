
cmake_minimum_required(VERSION 3.12)
project(Lab2)

set(CMAKE_CXX_STANDARD 20)

add_library(XMLParser src/XMLTextType.hpp src/XMLTokenType.hpp src/XMLAttribute.cpp src/XMLAttribute.hpp src/XMLElement.cpp src/XMLElement.hpp src/XMLDocument.cpp src/XMLDocument.hpp)

add_executable(XMLParserExec src/XMLTextType.hpp src/XMLTokenType.hpp src/XMLAttribute.cpp src/XMLAttribute.hpp src/XMLElement.cpp src/XMLElement.hpp src/XMLDocument.cpp src/XMLDocument.hpp tests/test.cpp)
