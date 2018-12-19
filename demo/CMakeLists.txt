cmake_minimum_required(VERSION 3.0)

if (MSVC)

else()    
    execute_process(COMMAND protoc -I=./ --cpp_out=./ ./demo.proto
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})    
endif()

include_directories(../src/)
include_directories(../proto/)

set(DEMO_SRC
    main.cpp
    demo.pb.h
    demo.pb.cc    
    ../proto/proto_message.pb.h    
    ../proto/proto_message.pb.cc
)

add_executable(tester ${DEMO_SRC})
target_link_libraries(tester ${PROTOBUF_LIBRARY})
target_link_libraries(tester lib_proto_message)