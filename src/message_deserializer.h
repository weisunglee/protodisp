#ifndef MESSAGE_DESERIALIZER_H_
#define MESSAGE_DESERIALIZER_H_

#include "proto_message.pb.h"
#include <string>
#include <memory>

// forward declaration
namespace google {
    namespace protobuf {
        class Message;
    }
}

namespace proto {
    class message_deserializer {
    public:
        message_deserializer() = delete;
        message_deserializer(const message_deserializer&) = delete;        
        message_deserializer& operator=(const message_deserializer&) = delete;
        message_deserializer(message_deserializer&&) = delete;
        message_deserializer& operator=(message_deserializer&&) = delete;

    public:
        static std::shared_ptr<google::protobuf::Message> deserialize(const char* buf, size_t length);

    private:
        static std::shared_ptr<google::protobuf::Message> create_message(const std::string& type_name);
    };
} // proto

#endif // MESSAGE_DESERIALIZER_H_