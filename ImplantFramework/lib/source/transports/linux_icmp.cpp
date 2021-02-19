/** @file linux_icmp.cpp
 * @brief Contains implementation for the ICMP transport
 * @author Im_Adriano
 */
#include "linux.hpp"
//TODO Implement this.

/** @namespace hivemind_lib
 * @brief The Hivemind library
 */
namespace hivemind_lib {
std::string LINUX_Icmp_Transport::SendAndReceive(std::string data) {
  return "";
}

void LINUX_Icmp_Transport::Send(std::string data) {

}

std::string LINUX_Icmp_Transport::Receive() {
  return "";
}
LINUX_Icmp_Transport::LINUX_Icmp_Transport(std::string hostname, std::string port)
    : Transport(std::move(hostname), std::move(port)) {

}
LINUX_Icmp_Transport::~LINUX_Icmp_Transport() {

}
}