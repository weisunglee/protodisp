#include "demo.pb.h"
#include <iostream>
#include "message_serializer.h"
#include "message_deserializer.h"
#include "message_handler.h"
#include "message_dispatcher.h"

int main()
{
  demo::demo_message_int dmi;
  dmi.set_data(100);
        
  demo::demo_message_string dms;
  dms.set_data("hello world");

  std::cout << dmi.data() << std::endl;
  std::cout << dms.data() << std::endl;  

  std::string dmi_serialized = proto::message_serializer::serialize(std::move(dmi));
  std::string dms_serialized = proto::message_serializer::serialize(std::move(dms));

  auto dmi_deserialized = proto::message_deserializer::deserialize(dmi_serialized.c_str(), dmi_serialized.length());
  auto dms_deserialized = proto::message_deserializer::deserialize(dms_serialized.c_str(), dms_serialized.length());

  std::cout << std::dynamic_pointer_cast<demo::demo_message_int>(dmi_deserialized)->data() << std::endl;
  std::cout << std::dynamic_pointer_cast<demo::demo_message_string>(dms_deserialized)->data() << std::endl;

  proto::message_dispatcher dispatcher([](proto::message_ptr<google::protobuf::Message>&& message){
    std::cout << "unknown message, type name:" << message->GetDescriptor()->full_name() << std::endl;
  });
    
  dispatcher.register_handler<demo::demo_message_string>([](proto::message_ptr<demo::demo_message_string>&& message){
    std::cout << message->data() << std::endl;
  });      
  
  proto::message_ptr<demo::demo_message_string> dms2 = std::make_shared<demo::demo_message_string>();
  dms2->set_data("dispatched");
  dispatcher.dispatch(std::move(dms2));

  proto::message_ptr<demo::demo_message_int> dmi2 = std::make_shared<demo::demo_message_int>();
  dmi2->set_data(200);
  dispatcher.dispatch(std::move(dmi2));

  return 0;
}
