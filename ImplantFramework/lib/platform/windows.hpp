#ifndef WINDOWS_H
#define WINDOWS_H

#include <utility>
#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <cstdlib>
#include <cstdio>
#include <map>
#include "transport.hpp"
#include "debugging.hpp"
#include "module.hpp"

namespace hivemind_lib {
/**
 * @brief WINDOWS implementation of the ICMP transport.
 */
class WindowsIcmpTransport : public Transport {
 public:
  std::string SendAndReceive(std::string data) override;
  void Send(std::string data) override;
  std::string Receive() override;
  WindowsIcmpTransport(std::string hostname, std::string port);
  ~WindowsIcmpTransport();
};

/**
 * @brief WINDOWS implementation of the TCP transport.
 */
class WindowsTcpTransport : public Transport {
 public:
  std::string SendAndReceive(std::string data) override;
  void Send(std::string data) override;
  std::string Receive() override;
  WindowsTcpTransport(const std::string &hostname, const std::string &port);
  ~WindowsTcpTransport();
 private:
  struct addrinfo *result = nullptr;

  /**
   * @brief Connect to the given host.
   * @return Status of connecting
   */
  SOCKET ConnectTo();
};

/**
 * @brief WINDOWS implementation of the UDP transport.
 */
class WindowsUdpTransport : public Transport {
 public:
  std::string SendAndReceive(std::string data) override;
  void Send(std::string data) override;
  std::string Receive() override;
  WindowsUdpTransport(std::string hostname, std::string port);
  ~WindowsUdpTransport();
};

/**
 * @brief WINDOWS Implementation of the PING module.
 */
class WindowsPingModule : public Module {
 public:
  ModuleInfo Init() override;
  std::string Ping(std::string host);
  WindowsPingModule();
};

/**
 * @brief Typedef to help with cross platform
 */
typedef WindowsTcpTransport TcpTransport;
/**
 * @brief Typedef to help with cross platform
 */
typedef WindowsIcmpTransport IcmpTransport;
/**
 * @brief Typedef to help with cross platform
 */
typedef WindowsUdpTransport UdpTransport;
/**
 * @brief Typedef to help with cross platform
 */
typedef WindowsPingModule PingModule;

}
#endif