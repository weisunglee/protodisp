#include "message_dispatcher.h"
#include <google/protobuf/message.h>

namespace proto {
    void message_dispatcher::dispatch(message_ptr<google::protobuf::Message>&& message) const {        
        if (!message) return;
        
        auto m = std::move(message); 
        handler_map::const_iterator it = handlers_.find(m->GetDescriptor());
        if(it != handlers_.end()) {
            it->second->on_message(std::move(m));
            return;
        }        

        if (error_handler_) {
            error_handler_(std::move(m));
            return;
        }        
    }
} // proto