/** @file icmp.cpp
 * @brief Contains implementation for the ICMP transport
 * @author Im_Adriano
 */
#include "transport.hpp"

/** @namespace hivemind_lib
 * @brief The Hivemind library
 */
namespace hivemind_lib {
/**
 * @brief ICMP transport implementation
*/
class Icmp_Transport : public Transport {
 public:
  std::string SendAndReceive(std::string data) {
    return "";
  }

  void Send(std::string data) {

  }

  std::string Receive() {
    return "";
  }
};
}