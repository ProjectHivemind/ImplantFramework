#ifndef WINDOWS_H
#define WINDOWS_H

#include "transport.hpp"

namespace hivemind_lib {

class WINDOWS_Icmp_Transport : public hivemind_lib::Transport {
 public:
  virtual std::string SendAndReceive(std::string data) = 0;
  virtual void Send(std::string data) = 0;
  virtual std::string Receive() = 0;
};

class WINDOWS_Tcp_Transport : public hivemind_lib::Transport {
 public:
  virtual std::string SendAndReceive(std::string data) = 0;
  virtual void Send(std::string data) = 0;
  virtual std::string Receive() = 0;
};

class WINDOWS_Udp_Transport : public hivemind_lib::Transport {
 public:
  virtual std::string SendAndReceive(std::string data) = 0;
  virtual void Send(std::string data) = 0;
  virtual std::string Receive() = 0;
};

typedef WINDOWS_Tcp_Transport Tcp_Transport;
typedef WINDOWS_Icmp_Transport Icmp_Transport;
typedef WINDOWS_Udp_Transport Udp_Transport;

}
#endif