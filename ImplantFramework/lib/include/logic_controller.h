#ifndef LOGIC_CONTROLLER_H
#define LOGIC_CONTROLLER_H
#include "transport.hpp"
#include "module.hpp"
#include <map>
#include <string>

namespace hivemind_lib {

class logic_controller {
 private:
  Transport_Enum transport_method;
  std::map<std::string, ModuleInfo> modules;
 public:
  logic_controller();

};
}
#endif
