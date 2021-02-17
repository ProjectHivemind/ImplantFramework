#include "logic_controller.hpp"

namespace hivemind_lib {
logic_controller::logic_controller() {
  ModuleInfo info;
  info.moduleDesc = "This contains the functions added separately from a module";
  info.moduleName = "EXTRA";
  this->modules.insert({info.moduleName, info});
  this->transport_method = None;
}

void logic_controller::AddFunction(void * func) {
  ModuleFuncInfo func_info;
  func_info.moduleFuncName = "Name here";
  func_info.moduleFuncDesc = "No Description";

  this->modules.at("EXTRA").moduleFuncs.push_back(func_info);
}

int logic_controller::RegisterBot() {
  return 0;
}

void logic_controller::BeginComms() {

}

void logic_controller::AddModule() {

}

void logic_controller::SetTransportMethod(Transport_Enum transport_enum) {
  this->transport_method = transport_enum;
}

void logic_controller::InitComms(std::string hostname, std::string port) {
  switch (this->transport_method) {
    case TCP:
      this->transport = std::make_unique<Tcp_Transport>(std::move(hostname), std::move(port));
      break;
    case UDP:
      this->transport = std::make_unique<Udp_Transport>(std::move(hostname), std::move(port));
      break;
    case ICMP:
      this->transport = std::make_unique<Icmp_Transport>(std::move(hostname), std::move(port));
      break;
    case None:

      break;
  }
}
}