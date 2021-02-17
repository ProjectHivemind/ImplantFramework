/** @file udp.cpp
 * @brief Contains implementation for the UDP transport
 * @author Im_Adriano
 */
#include <utility>

#include "windows.hpp"

/** @namespace hivemind_lib
 * @brief The Hivemind library
 */
namespace hivemind_lib {
std::string WINDOWS_Udp_Transport::SendAndReceive(std::string data) {
  return "";
}

void WINDOWS_Udp_Transport::Send(std::string data) {

}

std::string WINDOWS_Udp_Transport::Receive() {
  return "";
}
WINDOWS_Udp_Transport::WINDOWS_Udp_Transport(std::string hostname, std::string port)
    : Transport(std::move(hostname), std::move(port)) {

}
}