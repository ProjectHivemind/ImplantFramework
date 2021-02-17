/** @file linux_udp.cpp
 * @brief Contains implementation for the UDP transport
 * @author Im_Adriano
 */
#include "linux.hpp"

/** @namespace hivemind_lib
 * @brief The Hivemind library
 */
namespace hivemind_lib {
std::string LINUX_Udp_Transport::SendAndReceive(std::string data) {
  return "";
}

void LINUX_Udp_Transport::Send(std::string data) {

}

std::string LINUX_Udp_Transport::Receive() {
  return "";
}
LINUX_Udp_Transport::LINUX_Udp_Transport(std::string hostname, std::string port)
    : Transport(std::move(hostname), std::move(port)) {

}
LINUX_Udp_Transport::~LINUX_Udp_Transport() {

}
}