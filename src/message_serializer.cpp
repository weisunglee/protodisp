#include "message_serializer.h"

namespace proto {
    std::string message_serializer::wrap(std::string&& buf, const std::string& full_name) {
        proto::proto_message output_message;
        output_message.set_type(full_name);
        output_message.set_payload(buf);

        std::string result;
        output_message.SerializeToString(&result);

        return result;
    }
}
