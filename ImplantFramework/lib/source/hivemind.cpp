#include "hivemind.h"
#include "iostream"
#include "logic_controller.h"

namespace hivemind_lib {


int Init(){
  std::cout << "Init" << std::endl;

  return 0;
}

int AddFunction(void *) {
  std::cout << "Add Function" << std::endl;
  return 0;
}

int RegisterBot(CC_Info info) {
  std::cout << "Register Bot" << std::endl;
  std::cout << "Hostname: " << info.hostname << std::endl;
  std::cout << "Port: " << info.port << std::endl;

  return 0;
}

void BeginComms() {
  std::cout << "Begin Communications" << std::endl;
}

int UseTCP() {
  return 0;
}

int UseUDP() {
  return 0;
}

int UseICMP() {
  return 0;
}
}

