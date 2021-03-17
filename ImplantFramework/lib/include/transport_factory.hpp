/** @file transport_factory.hpp
 * @brief Factory to register modules to.
 * @author Im_Adriano
 */
#ifndef HIVEMIND_IMPLANTFRAMEWORK_LIB_INCLUDE_TRANSPORT_FACTORY_HPP_
#define HIVEMIND_IMPLANTFRAMEWORK_LIB_INCLUDE_TRANSPORT_FACTORY_HPP_

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <utility>
#include "transport.hpp"
#include "debugging.hpp"

namespace hivemind_lib {
/**
 * @brief Macro for class registration
 */
#define REGISTER_TRANSPORT_FACTORY(derivedClass, name) \
    namespace { auto registry_ ## derivedClass = ConcreteTransportFactory<derivedClass>(name);  }

class TransportFactory {
 private:
  using FactoryMap = std::map<std::string, TransportFactory *>;

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
  static void RegisterFactory(const std::string &name, TransportFactory *factory) {
    auto &reg = TransportFactory::GetRegister();
    reg[name] = factory;
  }

  /**
   * @brief Show all registered classes
   */
  static void ShowClasses() {
    DEBUG("Registered classes.", LEVEL_ERROR);
    DEBUG("===================", LEVEL_ERROR);
    for (const auto &pair: TransportFactory::GetRegister())
      DEBUG(" + " << pair.first, LEVEL_ERROR);
  }

  /**
   * @brief Get all registered classes
   */
  static std::vector<std::string> GetClasses() {
    std::vector<std::string> ret;
    for (const auto &pair: TransportFactory::GetRegister()) {
      ret.push_back(pair.first);
    }
    return ret;
  }

  /**
   * @brief Construct derived class returning a raw pointer
   * @param name Name of module to make
   * @return A pointer to an instance of the requested object
   */
  static Transport *MakeRaw(const std::string &name, const std::string &hostname, const std::string &port) {
    auto it = TransportFactory::GetRegister().find(name);
    if (it != TransportFactory::GetRegister().end())
      return it->second->Construct(hostname, port);
    return nullptr;
  }

  /**
   * @brief Construct derived class returning a unique pointer
   * @param name Name of module to make
   * @return A unique pointer to an instance of the requested object
   */
  static std::unique_ptr<Transport> MakeUnique(const std::string &name, const std::string &hostname, const std::string &port) {
    return std::unique_ptr<Transport>(TransportFactory::MakeRaw(name, hostname, port));
  }

  // Destructor
  virtual ~TransportFactory() = default;

  virtual Transport *Construct(const std::string &hostname, const std::string &port) const = 0;
};

template<typename DerivedClass>
class ConcreteTransportFactory : TransportFactory {
 public:
  // Register this global object on the Factory register
  explicit ConcreteTransportFactory(const std::string &name) {
    DEBUG("Transport Registered = " << name, LEVEL_INFO);
    TransportFactory::RegisterFactory(name, this);
  }
  Transport *Construct(const std::string &hostname, const std::string &port) const override {
    return new DerivedClass(hostname, port);
  }
};

}
#endif //HIVEMIND_IMPLANTFRAMEWORK_LIB_INCLUDE_MODULE_FACTORY_HPP_
