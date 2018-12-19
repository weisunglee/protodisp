#include "demo.pb.h"
#include <iostream>
#include "message_serializer.h"

int main()
{
  demo::demo_message_int dmi;
  dmi.set_data(100);
  std::cout << dmi.data() << std::endl;
  std::string dmi_serialized = proto::message_serializer::serialize(dmi);
    
  demo::demo_message_string dms;
  dms.set_data("hello world");
  std::cout << dms.data() << std::endl;  
  std::string dms_serialized = proto::message_serializer::serialize(dms);
    
  return 0;
}
