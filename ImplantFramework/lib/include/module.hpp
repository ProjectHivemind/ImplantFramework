/** @file module.hpp
 * @brief Defines the abstract class for Modules and it's related structs.
 * @author Im_Adriano
 */
#ifndef MODULE_H
#define MODULE_H

#include <map>
#include <string>
#include <vector>

/** @namespace hivemind_lib
 * @brief The Hivemind library
 */
namespace hivemind_lib {
/**
 * @brief Struct used to describe parameters needed for a given function in a module.
*/
struct ModuleFuncParamInfo {
  /// \brief The name of the parameter.
  std::string paramName;
  /// \brief The type of the parameter.
  std::string paramType;
};

/**
 * @brief Struct used to describe a callable function in this module.
*/
struct ModuleFuncInfo {
  /// \brief Name of the function.
  std::string moduleFuncName;
  /// \brief Description of the function.
  std::string moduleFuncDesc;
  /// \brief Number of parameters the function takes.
  int paramNum;
  /// \brief List of structs containing info about the function parameters.
  std::vector<ModuleFuncParamInfo> paramInfos;
};

/**
 * @brief Struct to describe a module.
*/
struct ModuleInfo {
  /// \brief Name of the module.
  std::string moduleName;
  /// \brief Description of the module.
  std::string moduleDesc;
  /// \brief List of structs containing info on the functions contained in the module.
  std::vector<ModuleFuncInfo> moduleFuncs;
};

/**
 * @brief Abstract class for modules. Forces certain variables and function to be created.
*/
class Module {
 public:
  /// \brief A map of function name to it's memory location. Used to help with abstraction.
  std::map<std::string, void *> funcMap;
  /// \brief A map of function names to it's respective timeout time.
  std::map<std::string, int> timeoutMap;
  /// \brief Struct containing info about the current module.
  ModuleInfo modInfo;

  /**
   * @brief Fill in the funcMap with function names and pointers to the functions.
   *		  Fill in timeoutMap with function names and values in seconds elapsed for which the function should be terminated.
   * @return modInfo completely filled out.
  */
  virtual ModuleInfo init() = 0;
};

/**
 * @brief Enum for available modules
 */
enum Module_Enum{
  All,
  Ping,
  Command_line
};
}

#endif
