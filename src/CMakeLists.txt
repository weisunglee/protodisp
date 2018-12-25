cmake_minimum_required(VERSION 3.0)

execute_process(COMMAND protoc -I=./ --cpp_out=./ ./proto_message.proto
WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../proto/) 

include_directories(../proto/)

set(LIB_PROTO_MESSAGE_SRC    
    message_serializer.h
    message_serializer.cpp        
    message_deserializer.h
    message_deserializer.cpp  
    message_handler.h
    message_dispatcher.h
    message_dispatcher.cpp      
    ../proto/proto_message.pb.h    
    ../proto/proto_message.pb.cc
)

set(HEADER_SRC
    message_serializer.h         
    message_deserializer.h    
    message_handler.h
    message_dispatcher.h    
    ../proto/proto_message.pb.h        
)

add_library(lib_proto_message SHARED ${LIB_PROTO_MESSAGE_SRC})
set_target_properties(lib_proto_message 
    PROPERTIES 
    OUTPUT_NAME "protodisp"
    PUBLIC_HEADER "${HEADER_SRC}"
)

add_library(lib_proto_message-static STATIC ${LIB_PROTO_MESSAGE_SRC})
set_target_properties(lib_proto_message-static
    PROPERTIES
    OUTPUT_NAME "protodisp"
    PREFIX "lib"
    PUBLIC_HEADER "${HEADER_SRC}"
)

install(TARGETS lib_proto_message lib_proto_message-static
    RUNTIME DESTINATION protodisp/bin
    LIBRARY DESTINATION protodisp/lib
    ARCHIVE DESTINATION protodisp/lib
    PUBLIC_HEADER DESTINATION protodisp/include
)