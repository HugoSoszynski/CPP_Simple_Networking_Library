cmake_minimum_required(VERSION 3.6)
project(CPP_Simple_Networking_Library)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    sources/Select.cpp
    sources/Socket.cpp
    sources/SocketException.cpp
)

include_directories(includes)

add_executable(CPP_Simple_Networking_Library ${SOURCE_FILES})