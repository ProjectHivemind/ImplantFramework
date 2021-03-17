/** @file udp.cpp
 * @brief Contains implementation for the UDP transport
 * @author Im_Adriano
 */
#include "windows.hpp"
//TODO Implement this.

/** @namespace hivemind_lib
 * @brief The Hivemind library
 */
namespace hivemind_lib {
std::string WindowsUdpTransport::SendAndReceive(std::string data) {
  return "";
}

void WindowsUdpTransport::Send(std::string data) {

}

std::string WindowsUdpTransport::Receive() {
  return "";
}

WindowsUdpTransport::WindowsUdpTransport(std::string hostname, std::string port)
    : Transport(std::move(hostname), std::move(port)) {

}
WindowsUdpTransport::~WindowsUdpTransport() {

}
}