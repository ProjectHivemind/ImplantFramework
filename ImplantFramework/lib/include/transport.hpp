/** @file
 * @brief Class hivemind_lib::Transport
 */
#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <string>

/** @namespace hivemind_lib
 * @brief The Hivemind library
 */
namespace hivemind_lib {
/**
 * @brief Abstract class for transport methods.
 * These are what actually send and recieve data from the central server.
*/
class Transport {
 public:
  /**
   * @brief Sends data to the server and waits to recieve a response.
   * @param  data Data to send to the server.
   * @return Data recieved from the server.
  */
  virtual std::string SendAndReceive(std::string data) = 0;

  /**
   * @brief Send data to the server.
   * @param data Data to send to the server.
  */
  virtual void Send(std::string data) = 0;

  /**
   * @brief Receive data from the server.
   * @return Data recieved from the server.
  */
  virtual std::string Receive() = 0;
};
}

#endif // !TRANSPORT_H
