cmake_minimum_required(VERSION 3.8)
project(source)

include_directories(CAutomata)
include_directories(CAutomata/Tests)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp)

set(SOURCE_FILES main.cpp CAutomata/cautomata.cpp CAutomata/Tests/CAutomataTests.cpp)
add_executable(source ${SOURCE_FILES})