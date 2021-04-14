/** @file module.hpp
 * @brief Defines the abstract class for Modules and it's related structs.
 * @author Im_Adriano
 */
#ifndef HIVEMIND_IMPLANTFRAMEWORK_LIB_INCLUDE_MODULE_HPP_
#define HIVEMIND_IMPLANTFRAMEWORK_LIB_INCLUDE_MODULE_HPP_

#include <map>
#include <string>
#include <vector>
#include <any>
#include <typeindex>
#include <typeinfo>

#include "json.hpp"

/** @namespace hivemind_lib
 * @brief The Hivemind library
 */
namespace hivemind_lib {
/**
 * @brief Struct used to describe a callable function in this module.
*/
struct ModuleFuncInfo {
  /// \brief Name of the function.
  std::string module_func_name;
  /// \brief Description of the function.
  std::string module_func_desc;
  /// \brief Number of parameters the function takes.
  int param_num = 0;
  /// \brief List of strings containing names for the function parameters.
  std::vector<std::string> param_names;
  /// \brief List of strings containing types for the function parameters.
  std::vector<std::string> param_types;
};

/**
 * @brief Struct to describe a module.
*/
struct ModuleInfo {
  /// \brief Name of the module.
  std::string module_name;
  /// \brief Description of the module.
  std::string module_desc;
  /// \brief List of structs containing info on the functions contained in the module.
  std::vector<ModuleFuncInfo> module_funcs;
};

/**
 * @brief Abstract class for modules. Forces certain variables and function to be created.
*/
class Module {
 public:
  /// \brief A map of function name to it's memory location. Used to help with abstraction.
  std::map<std::string, std::function<std::string(std::string)>> func_map_;
  /// \brief A map of function names to it's respective timeout time.
  std::map<std::string, int> timeout_map_;
  /// \brief Struct containing info about the current module.
  ModuleInfo mod_info_;

  /**
   * @brief Fill in the funcMap with function names and pointers to the functions.
   *		  Fill in timeoutMap with function names and values in seconds elapsed for which the function should be terminated.
   * @return modInfo completely filled out.
  */
  virtual ModuleInfo Init() = 0;
};

/**
 * @brief Parses json from string to a struct, used in module functions.
 * @tparam structType The struct type to fill out and return.
 * @param data The json to parse.
 * @return The struct filled with data from the parsed json.
 */
template<typename structType>
structType ParseData(std::string data) {
  nlohmann::json extract = nlohmann::json::parse(data);
  return extract.get<structType>();
}

/**
 * @brief Generate json parsing functions for struct.
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ModuleFuncInfo,
                                   module_func_name,
                                   module_func_desc,
                                   param_num,
                                   param_names,
                                   param_types);
/**
 * @brief Generate json parsing functions for struct.
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ModuleInfo, module_name, module_desc, module_funcs);

}

#endif
