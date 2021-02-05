/** @file udp.cpp
 * @brief Class hivemind_lib::Udp_Transport
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