#ifndef LINUX_H
#define LINUX_H

#include <utility>

#include "transport.hpp"
#include "debugging.hpp"
#include "module.hpp"

namespace hivemind_lib {
/**
 * @brief LINUX implementation of the ICMP transport.
 */
class LINUX_Icmp_Transport : public hivemind_lib::Transport {
 public:
  std::string SendAndReceive(std::string data) override;
  void Send(std::string data) override;
  std::string Receive() override;
  LINUX_Icmp_Transport(std::string hostname, std::string port);
  ~LINUX_Icmp_Transport();
};
/**
 * @brief LINUX implementation of the TCP transport.
 */
class LINUX_Tcp_Transport : public hivemind_lib::Transport {
 public:
  std::string SendAndReceive(std::string data) override;
  void Send(std::string data) override;
  std::string Receive() override;
  LINUX_Tcp_Transport(std::string hostname, std::string port);
  ~LINUX_Tcp_Transport();
 private:

};
/**
 * @brief LINUX implementation of the UDP transport.
 */
class LINUX_Udp_Transport : public hivemind_lib::Transport {
 public:
  std::string SendAndReceive(std::string data) override;
  void Send(std::string data) override;
  std::string Receive() override;
  LINUX_Udp_Transport(std::string hostname, std::string port);
  ~LINUX_Udp_Transport();
};

/**
 * @brief LINUX Implementation of the PING module.
 */
class LINUX_Ping_Module : public Module {
 public:
  ModuleInfo init() override;
  std::string ping(std::string host);
  LINUX_Ping_Module();
};

/**
 * @brief Typedef to help with cross platform
 */
typedef LINUX_Tcp_Transport Tcp_Transport;
/**
 * @brief Typedef to help with cross platform
 */
typedef LINUX_Icmp_Transport Icmp_Transport;
/**
 * @brief Typedef to help with cross platform
 */
typedef LINUX_Udp_Transport Udp_Transport;
/**
 * @brief Typedef to help with cross platform
 */
typedef LINUX_Ping_Module Ping_Module;

}
#endif