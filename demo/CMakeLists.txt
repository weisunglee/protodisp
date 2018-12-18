cmake_minimum_required(VERSION 3.0)

include(FindProtobuf)
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIR})
if (MSVC)

else()    
    execute_process(COMMAND protoc -I=./ --cpp_out=./ ./demo.proto
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})    
endif()

set(DEMO_SRC
    main.cpp
    demo.pb.cc
    demo.pb.h
)

add_executable(tester ${DEMO_SRC})
target_link_libraries(tester ${PROTOBUF_LIBRARY})