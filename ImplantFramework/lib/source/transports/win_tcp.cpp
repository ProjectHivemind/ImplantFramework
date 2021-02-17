/** @file win_tcp.cpp
 * @brief Contains implementation for the TCP transport
 * @author Im_Adriano
 */
#include <utility>
#include <iostream>

#include "windows.hpp"

/** @namespace hivemind_lib
 * @brief The Hivemind library
 */
namespace hivemind_lib {
std::string WINDOWS_Tcp_Transport::SendAndReceive(std::string data) {
  return "";
}

void WINDOWS_Tcp_Transport::Send(std::string data) {

}

std::string WINDOWS_Tcp_Transport::Receive() {
  return "";
}

WINDOWS_Tcp_Transport::WINDOWS_Tcp_Transport(std::string hostname, std::string port)
    : Transport(std::move(hostname), std::move(port)) {

}
}