/** @file transport.hpp
 * @brief Defines the abstract class for transports
 * @author Im_Adriano
 */
#ifndef HIVEMIND_IMPLANTFRAMEWORK_LIB_INCLUDE_TRANSPORT_HPP_
#define HIVEMIND_IMPLANTFRAMEWORK_LIB_INCLUDE_TRANSPORT_HPP_

#include <string>
#include <utility>

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
   * TODO Talk about removing.
  */
  virtual std::string Receive() = 0;

  Transport(std::string hostname, std::string port) {
    this->hostname_ = std::move(hostname);
    this->port_ = std::move(port);
  }

 private:
  /**
   * @brief Hostname to connect to for C&C
   */
  std::string hostname_;

  /**
   * @brief Port, if needed, to connect to for C&C
   */
  std::string port_;
};

/**
 * @brief Enum for available transports
 */
enum TransportEnum {
  NONE,
  TCP,
  UDP,
  ICMP
};
}

#endif // !TRANSPORT_H
