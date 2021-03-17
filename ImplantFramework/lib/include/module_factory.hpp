#ifndef HIVEMIND_IMPLANTFRAMEWORK_LIB_INCLUDE_MODULE_FACTORY_HPP_
#define HIVEMIND_IMPLANTFRAMEWORK_LIB_INCLUDE_MODULE_FACTORY_HPP_

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include "module.hpp"
#include "debugging.hpp"

namespace hivemind_lib {

// Macro for class registration
#define REGISTER_MODULE_FACTORY(derivedClass, name) \
    namespace { auto registry_ ## derivedClass = ConcreteModuleFactory<derivedClass>(name);  }

class ModuleFactory {
 private:
  using FactoryMap = std::map<std::string, ModuleFactory *>;

  static auto GetRegister() -> FactoryMap & {
    static FactoryMap class_register{};
    return class_register;
  }
 public:
  /** Register factory object of derived class */
  static
  auto RegisterFactory(const std::string &name, ModuleFactory *factory) -> void {
    auto &reg = ModuleFactory::GetRegister();
    reg[name] = factory;
  }
  /** Show all registered classes */
  static
  auto ShowClasses() -> void {
    DEBUG("Registered classes.", LEVEL_ERROR);
    DEBUG("===================", LEVEL_ERROR);
    for (const auto &pair: ModuleFactory::GetRegister())
      DEBUG(" + " << pair.first, LEVEL_ERROR);
  }
  /** Get all registered classes */
  static
  auto GetClasses() -> std::vector<std::string> {
    std::vector<std::string> ret;
    for (const auto &pair: ModuleFactory::GetRegister()){
      ret.push_back(pair.first);
    }
    return ret;
  }
  /**  Construct derived class returning a raw pointer */
  static
  auto MakeRaw(const std::string &name) -> Module * {
    auto it = ModuleFactory::GetRegister().find(name);
    if (it != ModuleFactory::GetRegister().end())
      return it->second->Construct();
    return nullptr;
  }

  /** Construct derived class returning an unique ptr  */
  static
  auto MakeUnique(const std::string &name) -> std::unique_ptr<Module> {
    return std::unique_ptr<Module>(ModuleFactory::MakeRaw(name));
  }

  // Destructor
  virtual
  ~ModuleFactory() = default;

  virtual
  auto Construct() const -> Module * = 0;
};

template<typename DerivedClass>
class ConcreteModuleFactory : ModuleFactory {
 public:
  // Register this global object on the Factory register
  explicit ConcreteModuleFactory(const std::string &name) {
    DEBUG("Module Registered = " << name, LEVEL_INFO);
    ModuleFactory::RegisterFactory(name, this);
  }
  auto Construct() const -> Module * override {
    return new DerivedClass;
  }
};

}
#endif //HIVEMIND_IMPLANTFRAMEWORK_LIB_INCLUDE_MODULE_FACTORY_HPP_
