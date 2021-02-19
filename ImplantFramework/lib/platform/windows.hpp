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

#define DEFAULT_BUFLEN 512

namespace hivemind_lib {
/**
 * @brief WINDOWS implementation of the ICMP transport.
 */
class WINDOWS_Icmp_Transport : public Transport {
 public:
  std::string SendAndReceive(std::string data) override;
  void Send(std::string data) override;
  std::string Receive() override;
  WINDOWS_Icmp_Transport(std::string hostname, std::string port);
  ~WINDOWS_Icmp_Transport();
};
/**
 * @brief WINDOWS implementation of the TCP transport.
 */
class WINDOWS_Tcp_Transport : public Transport {
 public:
  std::string SendAndReceive(std::string data) override;
  void Send(std::string data) override;
  std::string Receive() override;
  WINDOWS_Tcp_Transport(const std::string &hostname, const std::string &port);
  ~WINDOWS_Tcp_Transport();
 private:
  /**
   * @brief Connect to the given host.
   * @return Status of connecting
   */
  int ConnectTo();

  WSADATA wsaData{};
  SOCKET ConnectSocket = INVALID_SOCKET;
  struct addrinfo *result = nullptr,
      *ptr = nullptr,
      hints{};
  int iResult;
};
/**
 * @brief WINDOWS implementation of the UDP transport.
 */
class WINDOWS_Udp_Transport : public Transport {
 public:
  std::string SendAndReceive(std::string data) override;
  void Send(std::string data) override;
  std::string Receive() override;
  WINDOWS_Udp_Transport(std::string hostname, std::string port);
  ~WINDOWS_Udp_Transport();
};

/**
 * @brief WINDOWS Implementation of the PING module.
 */
class WINDOWS_Ping_Module : public Module {
 public:
  ModuleInfo init() override;
  std::string ping(std::string host);
  WINDOWS_Ping_Module();
};

/**
 * @brief Typedef to help with cross platform
 */
typedef WINDOWS_Tcp_Transport Tcp_Transport;
/**
 * @brief Typedef to help with cross platform
 */
typedef WINDOWS_Icmp_Transport Icmp_Transport;
/**
 * @brief Typedef to help with cross platform
 */
typedef WINDOWS_Udp_Transport Udp_Transport;
/**
 * @brief Typedef to help with cross platform
 */
typedef WINDOWS_Ping_Module Ping_Module;

}
#endif