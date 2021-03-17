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
// Macro for class registration
#define REGISTER_TRANSPORT_FACTORY(derivedClass, name) \
    namespace { auto registry_ ## derivedClass = ConcreteTransportFactory<derivedClass>(name);  }

class TransportFactory {
 private:
  using FactoryMap = std::map<std::string, TransportFactory *>;

  static auto GetRegister() -> FactoryMap & {
    static FactoryMap class_register{};
    return class_register;
  }
 public:
  /** Register factory object of derived class */
  static
  auto RegisterFactory(const std::string &name, TransportFactory *factory) -> void {
    auto &reg = TransportFactory::GetRegister();
    reg[name] = factory;
  }
  /** Show all registered classes */
  static
  auto ShowClasses() -> void {
    DEBUG("Registered classes.", LEVEL_ERROR);
    DEBUG("===================", LEVEL_ERROR);
    for (const auto &pair: TransportFactory::GetRegister())
      DEBUG(" + " << pair.first, LEVEL_ERROR);
  }
  /** Get all registered classes */
  static
  auto GetClasses() -> std::vector<std::string> {
    std::vector<std::string> ret;
    for (const auto &pair: TransportFactory::GetRegister()){
      ret.push_back(pair.first);
    }
    return ret;
  }
  /**  Construct derived class returning a raw pointer */
  static
  auto MakeRaw(const std::string &name, const std::string &hostname, const std::string &port) -> Transport * {
    auto it = TransportFactory::GetRegister().find(name);
    if (it != TransportFactory::GetRegister().end())
      return it->second->Construct(hostname, port);
    return nullptr;
  }

  /** Construct derived class returning an unique ptr  */
  static
  auto MakeUnique(const std::string &name, const std::string &hostname, const std::string &port) -> std::unique_ptr<Transport> {
    return std::unique_ptr<Transport>(TransportFactory::MakeRaw(name, hostname, port));
  }

  // Destructor
  virtual
  ~TransportFactory() = default;

  virtual
  auto Construct(const std::string &hostname, const std::string &port) const -> Transport * = 0;
};

template<typename DerivedClass>
class ConcreteTransportFactory : TransportFactory {
 public:
  // Register this global object on the Factory register
  explicit ConcreteTransportFactory(const std::string &name) {
    DEBUG("Transport Registered = " << name, LEVEL_INFO);
    TransportFactory::RegisterFactory(name, this);
  }
  auto Construct(const std::string &hostname, const std::string &port) const -> Transport * override {
    return new DerivedClass(hostname, port);
  }
};

}
#endif //HIVEMIND_IMPLANTFRAMEWORK_LIB_INCLUDE_MODULE_FACTORY_HPP_
