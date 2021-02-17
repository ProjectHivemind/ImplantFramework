/** @file linux_tcp.cpp
 * @brief Contains implementation for the TCP transport
 * @author Im_Adriano
 */
#include "linux.hpp"

/** @namespace hivemind_lib
 * @brief The Hivemind library
 */
namespace hivemind_lib {
std::string LINUX_Tcp_Transport::SendAndReceive(std::string data) {
  return "";
}

void LINUX_Tcp_Transport::Send(std::string data) {

}

std::string LINUX_Tcp_Transport::Receive() {
  return "";
}
LINUX_Tcp_Transport::LINUX_Tcp_Transport(std::string hostname, std::string port)
    : Transport(std::move(hostname), std::move(port)) {

}
LINUX_Tcp_Transport::~LINUX_Tcp_Transport() {

}
}
