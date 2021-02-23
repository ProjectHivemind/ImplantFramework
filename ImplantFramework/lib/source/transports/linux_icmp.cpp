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
std::string LinuxIcmpTransport::SendAndReceive(std::string data) {
  return "";
}

void LinuxIcmpTransport::Send(std::string data) {

}

std::string LinuxIcmpTransport::Receive() {
  return "";
}

LinuxIcmpTransport::LinuxIcmpTransport(std::string hostname, std::string port)
    : Transport(std::move(hostname), std::move(port)) {

}
LinuxIcmpTransport::~LinuxIcmpTransport() {

}
}