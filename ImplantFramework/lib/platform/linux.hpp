#ifndef LINUX_H
#define LINUX_H

#include "transport.hpp"

namespace hivemind_lib {

class LINUX_Icmp_Transport : public hivemind_lib::Transport {
 public:
  virtual std::string SendAndReceive(std::string data) = 0;
  virtual void Send(std::string data) = 0;
  virtual std::string Receive() = 0;
};

class LINUX_Tcp_Transport : public hivemind_lib::Transport {
 public:
  virtual std::string SendAndReceive(std::string data) = 0;
  virtual void Send(std::string data) = 0;
  virtual std::string Receive() = 0;
};

class LINUX_Udp_Transport : public hivemind_lib::Transport {
 public:
  virtual std::string SendAndReceive(std::string data) = 0;
  virtual void Send(std::string data) = 0;
  virtual std::string Receive() = 0;
};

typedef LINUX_Tcp_Transport Tcp_Transport;
typedef LINUX_Icmp_Transport Icmp_Transport;
typedef LINUX_Udp_Transport Udp_Transport;

}
#endif