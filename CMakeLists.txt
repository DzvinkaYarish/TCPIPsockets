cmake_minimum_required(VERSION 3.6)
project(sockets)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES_S server.cpp receive.h date.time.cpp date.time.h)
set(SOURCE_FILES_C client.cpp receive.h)
add_executable(server ${SOURCE_FILES_S})
add_executable(client ${SOURCE_FILES_C})