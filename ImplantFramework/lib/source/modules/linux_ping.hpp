/** @file linux_ping.hpp
 * @brief Contains implementation for the PING module
 * @author Im_Adriano
 */
#ifndef HIVEMIND_IMPLANTFRAMEWORK_LIB_SOURCE_MODULES_LINUX_PING_HPP_
#define HIVEMIND_IMPLANTFRAMEWORK_LIB_SOURCE_MODULES_LINUX_PING_HPP_
#include "module.hpp"
#include "module_factory.hpp"

namespace hivemind_lib {

/**
 * @brief LINUX Implementation of the PING module.
 */
class LinuxPingModule : public Module {

 public:
  ModuleInfo Init() override{
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

  std::string Ping(std::string host) {
    //TODO Implement this.
    return "";
  }

  LinuxPingModule() = default;
};

REGISTER_MODULE_FACTORY(LinuxPingModule, "PingModule");

}
#endif