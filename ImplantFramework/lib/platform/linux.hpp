#ifndef LINUX_H
#define LINUX_H

#include <utility>

#include "transport.hpp"

namespace hivemind_lib {

class LINUX_Icmp_Transport : public hivemind_lib::Transport {
 public:
  std::string SendAndReceive(std::string data) override;
  void Send(std::string data) override;
  std::string Receive() override;
  LINUX_Icmp_Transport(std::string hostname, std::string port);
};

class LINUX_Tcp_Transport : public hivemind_lib::Transport {
 public:
  std::string SendAndReceive(std::string data) override;
  void Send(std::string data) override;
  std::string Receive() override;
  LINUX_Tcp_Transport(std::string hostname, std::string port);
 private:

};

class LINUX_Udp_Transport : public hivemind_lib::Transport {
 public:
  std::string SendAndReceive(std::string data) override;
  void Send(std::string data) override;
  std::string Receive() override;
  LINUX_Udp_Transport(std::string hostname, std::string port);
};

typedef LINUX_Tcp_Transport Tcp_Transport;
typedef LINUX_Icmp_Transport Icmp_Transport;
typedef LINUX_Udp_Transport Udp_Transport;

}
#endif