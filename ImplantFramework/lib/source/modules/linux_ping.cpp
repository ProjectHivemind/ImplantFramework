#include "module.hpp"
#include "linux.hpp"

namespace hivemind_lib {

std::string LINUX_Ping_Module::ping(std::string host) {
  //TODO Implement this.
  return "";
}

ModuleInfo LINUX_Ping_Module::init() {
  struct ModuleFuncInfo module_func_info;

  module_func_info.paramNames.emplace_back("Host");
  module_func_info.paramTypes.emplace_back("STRING");
  module_func_info.moduleFuncName = "PING";
  module_func_info.paramNum = 1;

  this->modInfo.moduleFuncs.push_back(module_func_info);
  this->modInfo.moduleName = "PING";
  this->modInfo.moduleDesc = "A module to ping hosts";

  std::function < std::string(std::string) > f = std::bind(&LINUX_Ping_Module::ping, this, std::placeholders::_1);

  this->funcMap.insert({"PING", f});
  this->timeoutMap.insert({"PING", 60});

  return this->modInfo;
}

LINUX_Ping_Module::LINUX_Ping_Module() = default;
}
