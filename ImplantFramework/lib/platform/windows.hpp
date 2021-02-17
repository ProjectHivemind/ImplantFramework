#ifndef WINDOWS_H
#define WINDOWS_H

#include <utility>

#include "transport.hpp"

namespace hivemind_lib {

class WINDOWS_Icmp_Transport : public hivemind_lib::Transport {
 public:
  std::string SendAndReceive(std::string data) override;
  void Send(std::string data) override;
  std::string Receive() override;
  WINDOWS_Icmp_Transport(std::string hostname, std::string port);
};

class WINDOWS_Tcp_Transport : public hivemind_lib::Transport {
 public:
  std::string SendAndReceive(std::string data) override;
  void Send(std::string data) override;
  std::string Receive() override;
  WINDOWS_Tcp_Transport(std::string hostname, std::string port);
 private:

};

class WINDOWS_Udp_Transport : public hivemind_lib::Transport {
 public:
  std::string SendAndReceive(std::string data) override;
  void Send(std::string data) override;
  std::string Receive() override;
  WINDOWS_Udp_Transport(std::string hostname, std::string port);
};

typedef WINDOWS_Tcp_Transport Tcp_Transport;
typedef WINDOWS_Icmp_Transport Icmp_Transport;
typedef WINDOWS_Udp_Transport Udp_Transport;

}
#endif