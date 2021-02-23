#ifndef HIVEMIND_IMPLANTFRAMEWORK_LIB_PLATFORM_LINUX_HPP_
#define HIVEMIND_IMPLANTFRAMEWORK_LIB_PLATFORM_LINUX_HPP_

#include <utility>

#include "transport.hpp"
#include "debugging.hpp"
#include "module.hpp"

namespace hivemind_lib {
/**
 * @brief LINUX implementation of the ICMP transport.
 */
class LinuxIcmpTransport : public hivemind_lib::Transport {
 public:
  std::string SendAndReceive(std::string data) override;
  void Send(std::string data) override;
  std::string Receive() override;
  LinuxIcmpTransport(std::string hostname, std::string port);
  ~LinuxIcmpTransport();
};
/**
 * @brief LINUX implementation of the TCP transport.
 */
class LinuxTcpTransport : public hivemind_lib::Transport {
 public:
  std::string SendAndReceive(std::string data) override;
  void Send(std::string data) override;
  std::string Receive() override;
  LinuxTcpTransport(std::string hostname, std::string port);
  ~LinuxTcpTransport();
 private:

};
/**
 * @brief LINUX implementation of the UDP transport.
 */
class LinuxUdpTransport : public hivemind_lib::Transport {
 public:
  std::string SendAndReceive(std::string data) override;
  void Send(std::string data) override;
  std::string Receive() override;
  LinuxUdpTransport(std::string hostname, std::string port);
  ~LinuxUdpTransport();
};

/**
 * @brief LINUX Implementation of the PING module.
 */
class LinuxPingModule : public Module {
 public:
  ModuleInfo Init() override;
  std::string Ping(std::string host);
  LinuxPingModule();
};

/**
 * @brief Typedef to help with cross platform
 */
typedef LinuxTcpTransport TcpTransport;
/**
 * @brief Typedef to help with cross platform
 */
typedef LinuxIcmpTransport IcmpTransport;
/**
 * @brief Typedef to help with cross platform
 */
typedef LinuxUdpTransport UdpTransport;
/**
 * @brief Typedef to help with cross platform
 */
typedef LinuxPingModule PingModule;

}
#endif