/** @file linux_tcp.hpp
 * @brief Contains implementation for the TCP transport
 * @author Im_Adriano
 */
//TODO Implement this.
#ifndef HIVEMIND_IMPLANTFRAMEWORK_LIB_SOURCE_TRANSPORTS_LINUX_TCP_HPP_
#define HIVEMIND_IMPLANTFRAMEWORK_LIB_SOURCE_TRANSPORTS_LINUX_TCP_HPP_
#include <string>
#include "transport.hpp"
#include "transport_factory.hpp"

/** @namespace hivemind_lib
 * @brief The Hivemind library
 */
namespace hivemind_lib {

/**
 * @brief LINUX implementation of the TCP transport.
 */
class LinuxTcpTransport : public hivemind_lib::Transport {
 public:
  std::string SendAndReceive(std::string data) override {
    return "";
  }

  void Send(std::string data) override {

  }

  std::string Receive() override {
    return "";
  }

  LinuxTcpTransport(std::string hostname, std::string port)
      : Transport(std::move(hostname), std::move(port)) {

  }

  ~LinuxTcpTransport() = default;
};
REGISTER_TRANSPORT_FACTORY(LinuxTcpTransport, "TCP");
}
#endif