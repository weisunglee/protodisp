#include "message_deserializer.h"

namespace proto {
    std::shared_ptr<google::protobuf::Message> message_deserializer::deserialize(const char* buf, size_t length) {

        proto::proto_message proto_message;
        proto_message.ParseFromArray(buf, length);
        
        if(auto message = create_message(proto_message.type())) {
            message->ParseFromString(proto_message.payload());
            return message;
        }

        return nullptr;
    }

    std::shared_ptr<google::protobuf::Message> message_deserializer::create_message(const std::string& type_name) {
                
        if(auto descriptor = google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(type_name)) {
            if(auto prototype = google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor)) {
                return std::shared_ptr<google::protobuf::Message>(prototype->New());
            }
        }

        return nullptr;
    }

} // proto