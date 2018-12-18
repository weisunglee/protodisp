#include "demo.pb.h"
#include <iostream>

int main()
{
  demo::demo_message_int dmi;
  dmi.set_data(100);
  
  demo::demo_message_string dms;
  dms.set_data("hello world");

  std::cout << dmi.data() << std::endl;
  std::cout << dms.data() << std::endl;
    
  return 0;
}
