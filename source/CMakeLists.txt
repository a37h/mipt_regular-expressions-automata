cmake_minimum_required(VERSION 3.8)
project(source)

include_directories(CAutomata)
include_directories(CSolver)
include_directories(CSolver/CRotation)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp)

set(SOURCE_FILES main.cpp CAutomata/cautomata.cpp
        CSolver/csolver.cpp CSolver/CRotation/crotation.cpp)
add_executable(source ${SOURCE_FILES})