/** @file udp.cpp
 * @brief Contains implementation for the UDP transport
 * @author Im_Adriano
 */
#include "transport.hpp"

/** @namespace hivemind_lib
 * @brief The Hivemind library
 */
namespace hivemind_lib {
/**
 * @brief UDP transport implementation.
*/
class Udp_Transport : public Transport {
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