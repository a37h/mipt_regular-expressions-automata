cmake_minimum_required(VERSION 3.8)
project(source)

include_directories(CAutomata)
include_directories(CAutomata/Tests)
include_directories(CSolver)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp)

set(SOURCE_FILES main.cpp CAutomata/cautomata.cpp CAutomata/Tests/CAutomataTests.cpp CSolver/csolver.cpp)
add_executable(source ${SOURCE_FILES})