cmake_minimum_required(VERSION 3.0)
set(PROJECT_NAME "protobuf_reflection")

project(${PROJECT_NAME} C CXX)

include(FindProtobuf)
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIR})

add_subdirectory(./demo)
add_subdirectory(./src)