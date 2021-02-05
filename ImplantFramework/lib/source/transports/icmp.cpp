/** @file icmp.cpp
 * @brief Class hivemind_lib::Icmp_Transport
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