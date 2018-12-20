#ifndef MESSAGE_HANDLER_H_
#define MESSAGE_HANDLER_H_

#include <memory>
#include <functional>

// forward declaration
namespace google {
    namespace protobuf {
        class Message;
    }
}

namespace proto {

    class message_handler_interface {
    public:
        virtual ~message_handler_interface() = default;
        virtual void on_message(std::shared_ptr<google::protobuf::Message>&& message) = 0;
    };

    template<typename T>
    class message_handler_base {
    public:
        void on_message(std::shared_ptr<google::protobuf::Message>&& message) override {
            static_cast<T*>(this)->on_message(message);
        }        
    };

    template<typename T>
    class message_handler : public message_handler_base<message_handler<T>> {
    public:
        typedef std::function<void>(std::shared_ptr<T>&& message) handler_type;
        
        message_handler(const handler_type& handler)
            : handler_(handler) {}

        message_handler(handler_type&& handler)
            : handler_(handler) {}

        void on_message(std::shared_ptr<google::protobuf::Message>&& message) {            
            handler_(std::dynamic_pointer_case<T>(message));
        }

    private:
        //message_handler() = delete;
        

    private:
        handler_type handler_;
    };


} // proto

#endif // MESSAGE_HANDLER_H_
