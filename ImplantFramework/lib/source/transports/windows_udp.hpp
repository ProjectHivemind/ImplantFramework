/** @file windows_udp.hpp
 * @brief Contains implementation for the UDP transport
 * @author Im_Adriano
 */
//TODO Implement this.
#ifndef HIVEMIND_IMPLANTFRAMEWORK_LIB_SOURCE_TRANSPORTS_WINDOWS_UDP_HPP_
#define HIVEMIND_IMPLANTFRAMEWORK_LIB_SOURCE_TRANSPORTS_WINDOWS_UDP_HPP_
#include <string>
#include "transport.hpp"
#include "transport_factory.hpp"

/** @namespace hivemind_lib
 * @brief The Hivemind library
 */
namespace hivemind_lib {
/**
 * @brief WINDOWS implementation of the UDP transport.
 */
class WindowsUdpTransport : public Transport {
 public:
  std::string SendAndReceive(std::string data) override {
    return "";
  }
  void Send(std::string data) override {

  }
  std::string Receive() override {
    return "";
  }
  WindowsUdpTransport(std::string hostname, std::string port)
      : Transport(std::move(hostname), std::move(port)) {

  }
  ~WindowsUdpTransport() = default;
};

REGISTER_TRANSPORT_FACTORY(WindowsUdpTransport, "UDP");
}
#endif