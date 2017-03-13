cmake_minimum_required(VERSION 3.4)
find_package(PropWare 2.0.0)
project(pinControl)



set(CMAKE_CXX_STANDARD 11)
set(BOARD QUICKSTART)
set(MODEL cmm)
set(LINK_TINY ON)

set(SOURCE_FILES
        testPins.cpp
        pinClasses/pinGroup.h
        pinClasses/pin.h
        )
create_simple_executable(pinControl ${SOURCE_FILES})