#ifndef MESSAGE_DISPATCHER_H_
#define MESSAGE_DISPATCHER_H_

#include "message_handler.h"
#include <unordered_map>

// forward declaration
namespace google {
    namespace protobuf {
        class Descriptor;
    }
}

namespace proto {
    class message_dispatcher {
    public:
        template<typename T>
        void register_handler(typename message_handler<T>::handler_type&& handler);

    private:
        typedef std::unordered_map<const google::protobuf::Descriptor*, std::shared_ptr<message_handler_interface>> handler_map;
    };
} // proto

#endif // MESSAGE_DISPATCHER_H_