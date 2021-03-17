/** @file linux_tcp.cpp
 * @brief Contains implementation for the TCP transport
 * @author Im_Adriano
 */
#include "linux.hpp"
//TODO Implement this.

/** @namespace hivemind_lib
 * @brief The Hivemind library
 */
namespace hivemind_lib {
std::string LinuxTcpTransport::SendAndReceive(std::string data) {
  return "";
}

void LinuxTcpTransport::Send(std::string data) {

}

std::string LinuxTcpTransport::Receive() {
  return "";
}

LinuxTcpTransport::LinuxTcpTransport(std::string hostname, std::string port)
    : Transport(std::move(hostname), std::move(port)) {

}
LinuxTcpTransport::~LinuxTcpTransport() {

}
}
