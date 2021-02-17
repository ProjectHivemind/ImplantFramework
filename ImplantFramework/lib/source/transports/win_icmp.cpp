/** @file win_icmp.cpp
 * @brief Contains implementation for the ICMP transport
 * @author Im_Adriano
 */
#include <utility>

#include "windows.hpp"

/** @namespace hivemind_lib
 * @brief The Hivemind library
 */
namespace hivemind_lib {
std::string WINDOWS_Icmp_Transport::SendAndReceive(std::string data) {
  return "";
}

void WINDOWS_Icmp_Transport::Send(std::string data) {

}

std::string WINDOWS_Icmp_Transport::Receive() {
  return "";
}
WINDOWS_Icmp_Transport::WINDOWS_Icmp_Transport(std::string hostname, std::string port)
  : Transport(std::move(hostname), std::move(port)) {

}
}