/** @file module_factory.hpp
 * @brief Factory to register modules to.
 * @author Im_Adriano
 */
#ifndef HIVEMIND_IMPLANTFRAMEWORK_LIB_INCLUDE_MODULE_FACTORY_HPP_
#define HIVEMIND_IMPLANTFRAMEWORK_LIB_INCLUDE_MODULE_FACTORY_HPP_

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include "module.hpp"
#include "debugging.hpp"

namespace hivemind_lib {

/**
 * @brief Macro for class registration
 */
#define REGISTER_MODULE_FACTORY(derivedClass, name) \
    namespace { auto registry_ ## derivedClass = ConcreteModuleFactory<derivedClass>(name);  }

class ModuleFactory {
 private:
  using FactoryMap = std::map<std::string, ModuleFactory *>;

  static FactoryMap &GetRegister() {
    static FactoryMap class_register{};
    return class_register;
  }

 public:
  /**
   * @brief Registers a factory, do not call directly
   * @param name Name to store factory under
   * @param factory Factory to store
   */
  static void RegisterFactory(const std::string &name, ModuleFactory *factory) {
    auto &reg = ModuleFactory::GetRegister();
    reg[name] = factory;
  }

  /**
   * @brief Show all registered classes
   */
  static void ShowClasses() {
    DEBUG("Registered classes.", LEVEL_ERROR);
    DEBUG("===================", LEVEL_ERROR);
    for (const auto &pair: ModuleFactory::GetRegister())
      DEBUG(" + " << pair.first, LEVEL_ERROR);
  }

  /**
   * @brief Get all registered classes
   */
  static std::vector<std::string> GetClasses() {
    std::vector<std::string> ret;
    for (const auto &pair: ModuleFactory::GetRegister()) {
      ret.push_back(pair.first);
    }
    return ret;
  }

  /**
   * @brief Construct derived class returning a raw pointer
   * @param name Name of module to make
   * @return A pointer to an instance of the requested object
   */
  static Module *MakeRaw(const std::string &name) {
    auto it = ModuleFactory::GetRegister().find(name);
    if (it != ModuleFactory::GetRegister().end())
      return it->second->Construct();
    return nullptr;
  }

  /**
   * @brief Construct derived class returning a unique pointer
   * @param name Name of module to make
   * @return A unique pointer to an instance of the requested object
   */
  static std::unique_ptr<Module> MakeUnique(const std::string &name) {
    return std::unique_ptr<Module>(ModuleFactory::MakeRaw(name));
  }

  // Destructor
  virtual ~ModuleFactory() = default;

  virtual Module *Construct() const = 0;
};

template<typename DerivedClass>
class ConcreteModuleFactory : ModuleFactory {
 public:
  explicit ConcreteModuleFactory(const std::string &name) {
    DEBUG("Module Registered = " << name, LEVEL_INFO);
    ModuleFactory::RegisterFactory(name, this);
  }

  Module *Construct() const override {
    return new DerivedClass;
  }
};

}
#endif //HIVEMIND_IMPLANTFRAMEWORK_LIB_INCLUDE_MODULE_FACTORY_HPP_
