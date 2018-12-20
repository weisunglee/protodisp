#include "demo.pb.h"
#include <iostream>
#include "message_serializer.h"
#include "message_deserializer.h"

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
    
  return 0;
}
