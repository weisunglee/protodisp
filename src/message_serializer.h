#ifndef MESSAGE_SERIALIZER_H_
#define MESSAGE_SERIALIZER_H_

#include <string>
#include "proto_message.pb.h"

namespace proto {
    class message_serializer {
    public:    
        message_serializer() = delete;        
        message_serializer(const message_serializer&) = delete;
        message_serializer& operator=(const message_serializer&) = delete;
        message_serializer(message_serializer&&) = delete;
        message_serializer& operator=(message_serializer&&) = delete;
        
    public:
        template<typename T>
        static std::string serialize(T&& message);

    private:
        template<typename T>
        static std::string serialize(T&& message, const std::string& full_name);
        static std::string wrap(std::string&& buf, const std::string& full_name);        
    };

    template<typename T>
    std::string message_serializer::serialize(T&& message) {
        return message_serializer::serialize(message, message.descriptor()->full_name());
    }

    template<typename T>
    std::string message_serializer::serialize(T&& message, const std::string& full_name) {
        std::string buf;
        message.SerializeToString(&buf);

        return wrap(std::move(buf), full_name);
    }

} // proto

#endif // MESSAGE_SERIALIZER_H_
