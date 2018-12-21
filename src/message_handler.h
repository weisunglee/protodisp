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

    template<typename T>
    using message_ptr = std::shared_ptr<T>;

    class message_handler_interface {
    public:
        virtual ~message_handler_interface() = default;
        virtual void on_message(message_ptr<google::protobuf::Message>&& message) = 0;
    };

    template<typename T>
    class message_handler_base : public message_handler_interface {
    public:
        message_handler_base() = default;
        message_handler_base(const message_handler_base&) = delete;        
        message_handler_base& operator=(const message_handler_base&) = delete;
        message_handler_base(message_handler_base&&) = delete;
        message_handler_base& operator=(message_handler_base&&) = delete;

    public:
        void on_message(message_ptr<google::protobuf::Message>&& message) override {
            static_cast<T*>(this)->on_message(std::move(message));
        }        
    };    

    template<typename T>
    using handler_type =  std::function<void (message_ptr<T>&& message)>;

    template<typename T>
    class message_handler : public message_handler_base<message_handler<T>> {
    public:
        message_handler() = delete;

    public:                    
        message_handler(const handler_type<T>& handler)
            : handler_(handler) {}

        message_handler(handler_type<T>&& handler)
            : handler_(handler) {}

        void on_message(message_ptr<google::protobuf::Message>&& message) const {
            handler_(std::dynamic_pointer_cast<T>(message));
        }
                
    private:
        handler_type<T> handler_;        
    };
    
} // proto

#endif // MESSAGE_HANDLER_H_
