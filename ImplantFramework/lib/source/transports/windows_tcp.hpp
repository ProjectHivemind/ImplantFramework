/** @file windows_tcp.hpp
 * @brief Contains implementation for the TCP transport
 * @author Im_Adriano
 */
#ifndef HIVEMIND_IMPLANTFRAMEWORK_LIB_SOURCE_TRANSPORTS_WINDOWS_TCP_HPP_
#define HIVEMIND_IMPLANTFRAMEWORK_LIB_SOURCE_TRANSPORTS_WINDOWS_TCP_HPP_
#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <cstdlib>
#include <cstdio>
#include <map>
#include "transport.hpp"
#include "debugging.hpp"
#include "transport_factory.hpp"

/** @namespace hivemind_lib
 * @brief The Hivemind library
 */
namespace hivemind_lib {

#define DEFAULT_BUFLEN 9000

/**
 * @brief WINDOWS implementation of the TCP transport.
 */
class WindowsTcpTransport : public Transport {
 public:
  std::string SendAndReceive(std::string data) override {
    int i_result;

    SOCKET connect_socket = this->ConnectTo();
    if (connect_socket == INVALID_SOCKET) {
      DEBUG("ERROR WITH SOCKET", LEVEL_ERROR);
      return "";
    }

    i_result = send(connect_socket, data.c_str(), (int) strlen(data.c_str()), 0);
    if (i_result == SOCKET_ERROR) {
      DEBUG("send failed with error: " << WSAGetLastError(), LEVEL_ERROR);
      closesocket(connect_socket);
      WSACleanup();
      return "";
    }

    // shutdown the connection since no more data will be sent
    i_result = shutdown(connect_socket, SD_SEND);
    if (i_result == SOCKET_ERROR) {
      printf("shutdown failed with error: %d\n", WSAGetLastError());
      closesocket(connect_socket);
      WSACleanup();
      return "";
    }

    // Receive until the peer closes the connection
    char buf[DEFAULT_BUFLEN];

    int len = DEFAULT_BUFLEN;
    std::string ret;
    do {
      memset(buf, 0, sizeof(buf));
      i_result = recv(connect_socket, buf, len, 0);
      if (i_result > 0) {
        DEBUG("Bytes received: " << i_result, LEVEL_INFO);
        ret += buf;
      } else if (i_result == 0) {
        DEBUG("Connection closed", LEVEL_INFO);
      } else {
        DEBUG("recv failed with error: " << WSAGetLastError(), LEVEL_ERROR);
        return "";
      }
    } while (i_result > 0);

    closesocket(connect_socket);
    return ret;
  }

  void Send(std::string data) override {
    int i_result;

    SOCKET connect_socket = this->ConnectTo();
    if (connect_socket == INVALID_SOCKET) {
      DEBUG("ERROR WITH SOCKET", LEVEL_ERROR);
    }

    i_result = send(connect_socket, data.c_str(), (int) strlen(data.c_str()), 0);
    if (i_result == SOCKET_ERROR) {
      DEBUG("send failed with error: " << WSAGetLastError(), LEVEL_ERROR);
      closesocket(connect_socket);
      WSACleanup();
    }

    DEBUG("Bytes Sent: " << i_result, LEVEL_DEBUG);

    closesocket(connect_socket);
  }

  std::string Receive() override {
    return "";
  }

  WindowsTcpTransport(const std::string &hostname, const std::string &port)
      : Transport(hostname, port) {
    WSADATA wsa_data{};
    struct addrinfo hints{};
    int i_result;
    // Initialize Winsock
    i_result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (i_result != 0) {
      DEBUG("WSAStartup failed with error: " << i_result, LEVEL_ERROR);
      exit(1);
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    i_result = getaddrinfo(hostname.c_str(), port.c_str(), &hints, &result);
    if (i_result != 0) {
      DEBUG("getaddrinfo failed with error: " << i_result, LEVEL_ERROR);
      WSACleanup();
      exit(1);
    }
  }

  ~WindowsTcpTransport() {
    freeaddrinfo(result);
    WSACleanup();
  }

 private:
  struct addrinfo *result = nullptr;

  /**
   * @brief Connect to the given host.
   * @return Status of connecting
   */
  SOCKET ConnectTo() {


    auto connect_socket = INVALID_SOCKET;
    int i_result;
    addrinfo *ptr;

    // Initialize Winsock
    WSADATA wsa_data{};
    i_result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (i_result != 0) {
      DEBUG("WSAStartup failed with error: " << i_result, LEVEL_ERROR);
      return INVALID_SOCKET;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != nullptr; ptr = ptr->ai_next) {

      // Create a SOCKET for connecting to server
      connect_socket = socket(ptr->ai_family, ptr->ai_socktype,
                              ptr->ai_protocol);
      if (connect_socket == INVALID_SOCKET) {
        DEBUG("socket failed with error: " << WSAGetLastError(), LEVEL_ERROR);
        WSACleanup();
        return INVALID_SOCKET;
      }

      // Connect to server.
      i_result = connect(connect_socket, ptr->ai_addr, (int) ptr->ai_addrlen);
      if (i_result == SOCKET_ERROR) {
        closesocket(connect_socket);
        connect_socket = INVALID_SOCKET;
        continue;
      }
      break;
    }

    if (connect_socket == INVALID_SOCKET) {
      DEBUG("Unable to connect to server!", LEVEL_ERROR);
      WSACleanup();
      return INVALID_SOCKET;
    }

    return connect_socket;
  }
};

REGISTER_TRANSPORT_FACTORY(WindowsTcpTransport, "TCP");

}
#endif