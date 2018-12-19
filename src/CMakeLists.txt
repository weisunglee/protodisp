cmake_minimum_required(VERSION 3.0)

if (MSVC)

else()    
    execute_process(COMMAND protoc -I=./ --cpp_out=./ ./proto_message.proto
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../proto/) 
endif()

include_directories(../proto/)

set(LIB_PROTO_MESSAGE_SRC    
    message_serializer.h
    message_serializer.cpp    
    #proto_message.pb.cc
    #proto_message.pb.h
)

add_library(lib_proto_message ${LIB_PROTO_MESSAGE_SRC})
#target_link_libraries(tester ${PROTOBUF_LIBRARY})