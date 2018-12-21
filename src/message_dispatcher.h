#ifndef MESSAGE_DISPATCHER_H_
#define MESSAGE_DISPATCHER_H_

#include "message_handler.h"
#include <unordered_map>

// forward declaration
namespace google {
    namespace protobuf {
        class Descriptor;
        class Message;
    }
}

namespace proto {

    using handler_map = std::unordered_map<const google::protobuf::Descriptor*, message_ptr<message_handler_interface>>;

    class message_dispatcher {
    public:
        template<typename T>
        void register_handler(handler_type<T>&& handler);
        void dispatch(message_ptr<google::protobuf::Message>&& message) const;      

    private:
        handler_map handlers_;    
    };

    template<typename T>
    void message_dispatcher::register_handler(handler_type<T>&& handler) {
        message_ptr<message_handler_interface> handler_ptr = std::make_shared<message_handler<T>>(handler);
        handlers_[T::descriptor()] = handler_ptr;
    }
} // proto

#endif // MESSAGE_DISPATCHER_H_