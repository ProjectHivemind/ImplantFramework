#include "module.hpp"
#include "linux.hpp"

namespace hivemind_lib {

std::string LinuxPingModule::Ping(std::string host) {
  //TODO Implement this.
  return "";
}

ModuleInfo LinuxPingModule::Init() {
  struct ModuleFuncInfo module_func_info;

  module_func_info.param_names.emplace_back("Host");
  module_func_info.param_types.emplace_back("STRING");
  module_func_info.module_func_name = "PING";
  module_func_info.param_num = 1;

  this->mod_info_.module_funcs.push_back(module_func_info);
  this->mod_info_.module_name = "PING";
  this->mod_info_.module_desc = "A module to Ping hosts";

  std::function < std::string(std::string) > f = std::bind(&LinuxPingModule::Ping, this, std::placeholders::_1);

  this->func_map_.insert({"PING", f});
  this->timeout_map_.insert({"PING", 60});

  return this->mod_info_;
}

LinuxPingModule::LinuxPingModule() = default;
}
