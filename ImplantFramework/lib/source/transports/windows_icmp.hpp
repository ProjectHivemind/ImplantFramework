/** @file windows_icmp.hpp
 * @brief Contains implementation for the ICMP transport
 * @author Im_Adriano
 */
#ifndef HIVEMIND_IMPLANTFRAMEWORK_LIB_SOURCE_TRANSPORTS_WINDOWS_ICMP_HPP_
#define HIVEMIND_IMPLANTFRAMEWORK_LIB_SOURCE_TRANSPORTS_WINDOWS_ICMP_HPP_
#include <string>
#include "transport.hpp"
#include "transport_factory.hpp"

//TODO Implement this.

/** @namespace hivemind_lib
 * @brief The Hivemind library
 */
namespace hivemind_lib {
/**
 * @brief WINDOWS implementation of the ICMP transport.
 */
class WindowsIcmpTransport : public Transport {
 public:
  std::string SendAndReceive(std::string data) override {
    return "";
  }

  void Send(std::string data) override {

  }

  std::string Receive() override {
    return "";
  }

  WindowsIcmpTransport(std::string hostname, std::string port)
      : Transport(std::move(hostname), std::move(port)) {

  }

  ~WindowsIcmpTransport() = default;
};

REGISTER_TRANSPORT_FACTORY(WindowsIcmpTransport, "ICMP");

}
#endif