/** @file win_icmp.cpp
 * @brief Contains implementation for the ICMP transport
 * @author Im_Adriano
 */
#include "windows.hpp"
//TODO Implement this.

/** @namespace hivemind_lib
 * @brief The Hivemind library
 */
namespace hivemind_lib {
std::string WindowsIcmpTransport::SendAndReceive(std::string data) {
  return "";
}

void WindowsIcmpTransport::Send(std::string data) {

}

std::string WindowsIcmpTransport::Receive() {
  return "";
}

WindowsIcmpTransport::WindowsIcmpTransport(std::string hostname, std::string port)
    : Transport(std::move(hostname), std::move(port)) {

}
WindowsIcmpTransport::~WindowsIcmpTransport() {

}
}