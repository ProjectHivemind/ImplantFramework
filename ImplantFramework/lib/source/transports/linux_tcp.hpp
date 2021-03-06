/** @file linux_tcp.hpp
 * @brief Contains implementation for the TCP transport
 * @author raydan4
 */
#ifndef HIVEMIND_IMPLANTFRAMEWORK_LIB_SOURCE_TRANSPORTS_LINUX_TCP_HPP_
#define HIVEMIND_IMPLANTFRAMEWORK_LIB_SOURCE_TRANSPORTS_LINUX_TCP_HPP_
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "transport.hpp"
#include "transport_factory.hpp"

/** @namespace hivemind_lib
 * @brief The Hivemind library
 */
namespace hivemind_lib {

#define DEFAULT_BUFLEN 1024

/**
 * @brief LINUX implementation of the TCP transport.
 */
class LinuxTcpTransport : public hivemind_lib::Transport {
 public:
  std::string SendAndReceive(std::string data) override {
    std::string ret = "";
    char buf[DEFAULT_BUFLEN];
    int len = DEFAULT_BUFLEN;
    int i_result;
   
    // Create socket
    int socket = this -> ConnectTo();
    if (socket < 0) {
      DEBUG("ERROR WITH SOCKET", LEVEL_ERROR);
      return "";
    }

    // Send data
    i_result = write(socket, data.c_str(), strlen(data.c_str()));
    if (i_result < 0) {
      DEBUG("ERROR WRITING TO SOCKET", LEVEL_ERROR);
      goto cleanup;
    } else {
      DEBUG("Bytes Sent:" << i_result, LEVEL_DEBUG);
    }

    // Shutdown sending
    shutdown(socket, SHUT_WR);

    // Receive data
    do {
      memset(buf, 0, sizeof(buf));
      i_result = read(socket, buf, len);
      if (i_result > 0) {
        DEBUG("Bytes received: " << i_result, LEVEL_INFO);
        ret += buf;
      } else if (i_result == 0) {
        DEBUG("Connection closed", LEVEL_INFO);
      } else {
        DEBUG("ERROR READING FROM SOCKET", LEVEL_ERROR);
        goto cleanup;
      }
    } while (i_result > 0);

    cleanup:
      close(socket);
      return ret;
  }

  void Send(std::string data) override {
    int i_result;

    // Create socket
    int socket = this -> ConnectTo();
    if (socket < 0) {
      DEBUG("ERROR WITH SOCKET", LEVEL_ERROR);
      return;
    }

    // Send data
    i_result = write(socket, data.c_str(), strlen(data.c_str()));
    if (i_result < 0) {
      DEBUG("ERROR WRITING TO SOCKET", LEVEL_ERROR);
      goto cleanup;
    } else {
      DEBUG("Bytes Sent: " << i_result, LEVEL_DEBUG);
    }

    cleanup:
      close(socket);
  }

  std::string Receive() override {
    return "";
  }

  LinuxTcpTransport(std::string hostname, std::string port)
      : Transport(hostname, port) {
    struct hostent *server;

    server = gethostbyname(hostname.c_str());

    if (server == NULL) {
      DEBUG("ERROR RESOLVING SERVER ADDRESS", LEVEL_ERROR);
      exit(1);
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    memcpy(server->h_addr, &server_address.sin_addr.s_addr, server->h_length);
    server_address.sin_port = htons(std::stoi(port));
  }

 private:
  struct sockaddr_in server_address;

  int ConnectTo() {
    int socketfd;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketfd < 0) {
      DEBUG("ERROR CREATING SOCKET", LEVEL_ERROR);
      return socketfd;
    }

    if (int status = connect(socketfd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
      DEBUG("ERROR CONNECTING TO SERVER", LEVEL_ERROR);
      close(socketfd);
      return status;
    }

    return socketfd;
  }

  ~LinuxTcpTransport() = default;
};

REGISTER_TRANSPORT_FACTORY(LinuxTcpTransport, "TCP");

}
#endif