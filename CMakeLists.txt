cmake_minimum_required(VERSION 3.6)
project(CPP_Simple_Networking_Library)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    sources/Socket.cpp
    )

add_executable(CPP_Simple_Networking_Library ${SOURCE_FILES})