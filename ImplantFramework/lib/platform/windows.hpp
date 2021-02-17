#ifndef WINDOWS_H
#define WINDOWS_H

#include <utility>
#include <iostream>
#define _WINSOCKAPI_
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstdlib>
#include <cstdio>
#include "transport.hpp"
#include "debugging.hpp"

#define DEFAULT_BUFLEN 512

namespace hivemind_lib {

class WINDOWS_Icmp_Transport : public hivemind_lib::Transport {
 public:
  std::string SendAndReceive(std::string data) override;
  void Send(std::string data) override;
  std::string Receive() override;
  WINDOWS_Icmp_Transport(std::string hostname, std::string port);
  ~WINDOWS_Icmp_Transport();
};

class WINDOWS_Tcp_Transport : public hivemind_lib::Transport {
 public:
  std::string SendAndReceive(std::string data) override;
  void Send(std::string data) override;
  std::string Receive() override;
  WINDOWS_Tcp_Transport(const std::string &hostname, const std::string &port);
  ~WINDOWS_Tcp_Transport();
 private:
  int ConnectTo();
  WSADATA wsaData{};
  SOCKET ConnectSocket = INVALID_SOCKET;
  struct addrinfo *result = nullptr,
      *ptr = nullptr,
      hints{};
  int iResult;
};

class WINDOWS_Udp_Transport : public hivemind_lib::Transport {
 public:
  std::string SendAndReceive(std::string data) override;
  void Send(std::string data) override;
  std::string Receive() override;
  WINDOWS_Udp_Transport(std::string hostname, std::string port);
  ~WINDOWS_Udp_Transport();
};

typedef WINDOWS_Tcp_Transport Tcp_Transport;
typedef WINDOWS_Icmp_Transport Icmp_Transport;
typedef WINDOWS_Udp_Transport Udp_Transport;

}
#endif