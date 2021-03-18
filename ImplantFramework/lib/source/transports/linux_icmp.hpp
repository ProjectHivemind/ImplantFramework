/** @file linux_icmp.hpp
 * @brief Contains implementation for the ICMP transport
 * @author Im_Adriano
 */
//TODO Implement this.
#ifndef HIVEMIND_IMPLANTFRAMEWORK_LIB_SOURCE_TRANSPORTS_LINUX_ICMP_HPP_
#define HIVEMIND_IMPLANTFRAMEWORK_LIB_SOURCE_TRANSPORTS_LINUX_ICMP_HPP_
#include <string>
#include "transport.hpp"
#include "transport_factory.hpp"

/** @namespace hivemind_lib
 * @brief The Hivemind library
 */
namespace hivemind_lib {
/**
 * @brief LINUX implementation of the ICMP transport.
 */
class LinuxIcmpTransport : public hivemind_lib::Transport {
 public:
  std::string SendAndReceive(std::string data) override {
    return "";
  }

  void Send(std::string data) override {

  }

  std::string Receive() override {
    return "";
  }

  LinuxIcmpTransport(std::string hostname, std::string port)
      : Transport(std::move(hostname), std::move(port)) {
  }

  ~LinuxIcmpTransport() = default;
};

REGISTER_TRANSPORT_FACTORY(LinuxIcmpTransport, "ICMP");

}
#endif