/** @file linux_udp.cpp
 * @brief Contains implementation for the UDP transport
 * @author Im_Adriano
 */
#include "linux.hpp"
//TODO Implement this.

/** @namespace hivemind_lib
 * @brief The Hivemind library
 */
namespace hivemind_lib {
std::string LinuxUdpTransport::SendAndReceive(std::string data) {
  return "";
}

void LinuxUdpTransport::Send(std::string data) {

}

std::string LinuxUdpTransport::Receive() {
  return "";
}

LinuxUdpTransport::LinuxUdpTransport(std::string hostname, std::string port)
    : Transport(std::move(hostname), std::move(port)) {

}
LinuxUdpTransport::~LinuxUdpTransport() {

}
}