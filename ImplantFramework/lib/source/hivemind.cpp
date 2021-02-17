#include "hivemind.h"

#include <utility>
#include "iostream"
#include "logic_controller.hpp"
#include "debugging.hpp"

namespace hivemind_lib {
logic_controller controller;

int Init(){
  DEBUG("Init", LEVEL_INFO);
  controller = logic_controller();
  return 0;
}

int AddFunction(void * func) {
  DEBUG("Add Function", LEVEL_INFO);
  controller.AddFunction(func);
  return 0;
}

void RegisterBot(CC_Info info) {
  DEBUG("Register Bot", LEVEL_INFO);
  DEBUG("Hostname->" << info.hostname, LEVEL_DEBUG);
  DEBUG("Port->" << info.port, LEVEL_DEBUG);
  controller.RegisterBot();
}

void BeginComms() {
  DEBUG("Begin Communications", LEVEL_INFO);
  controller.BeginComms();
}

int UseTCP() {
  DEBUG("USING TCP", LEVEL_INFO);
  controller.SetTransportMethod(TCP);
  return 0;
}

int UseUDP() {
  DEBUG("USING UDP", LEVEL_INFO);
  controller.SetTransportMethod(UDP);
  return 0;
}

int UseICMP() {
  DEBUG("USING ICMP", LEVEL_INFO);
  controller.SetTransportMethod(ICMP);
  return 0;
}

int InitComms(std::string hostname, std::string port){
  DEBUG("INIT Communications", LEVEL_INFO);
  controller.InitComms(std::move(hostname), std::move(port));
  return 0;
}
}
