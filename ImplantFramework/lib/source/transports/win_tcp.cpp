/** @file win_tcp.cpp
 * @brief Contains implementation for the TCP transport
 * @author Im_Adriano
 */

#include "windows.hpp"

/** @namespace hivemind_lib
 * @brief The Hivemind library
 */
namespace hivemind_lib {

int WINDOWS_Tcp_Transport::ConnectTo() {
  // Attempt to connect to an address until one succeeds
  for (ptr = result; ptr != nullptr; ptr = ptr->ai_next) {

    // Create a SOCKET for connecting to server
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
                           ptr->ai_protocol);
    if (ConnectSocket == INVALID_SOCKET) {
      DEBUG("socket failed with error: " << WSAGetLastError(), LEVEL_ERROR);
      WSACleanup();
      return 1;
    }

    // Connect to server.
    iResult = connect(ConnectSocket, ptr->ai_addr, (int) ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
      closesocket(ConnectSocket);
      ConnectSocket = INVALID_SOCKET;
      continue;
    }
    break;
  }

  if (ConnectSocket == INVALID_SOCKET) {
    DEBUG("Unable to connect to server!", LEVEL_ERROR);
    WSACleanup();
    return 1;
  }

  return 0;
}

std::string WINDOWS_Tcp_Transport::SendAndReceive(std::string data) {
  this->ConnectTo();

  iResult = send(ConnectSocket, data.c_str(), (int) strlen(data.c_str()), 0);
  if (iResult == SOCKET_ERROR) {
    DEBUG("send failed with error: " << WSAGetLastError(), LEVEL_ERROR);
    closesocket(ConnectSocket);
    WSACleanup();
  }
  // Receive until the peer closes the connection
  char buf[DEFAULT_BUFLEN];
  int len = DEFAULT_BUFLEN;
  std::string ret;
  do {
    iResult = recv(ConnectSocket, buf, len, 0);
    if (iResult > 0) {
      DEBUG("Bytes received: " << iResult, LEVEL_INFO);
      ret += buf;
    } else if (iResult == 0) {
      DEBUG("Connection closed", LEVEL_INFO);
    } else {
      DEBUG("recv failed with error: " << WSAGetLastError(), LEVEL_ERROR);
    }
  } while (iResult > 0);

  // cleanup
  closesocket(ConnectSocket);
  return ret;
}

void WINDOWS_Tcp_Transport::Send(std::string data) {
  this->ConnectTo();

  iResult = send(ConnectSocket, data.c_str(), (int) strlen(data.c_str()), 0);
  if (iResult == SOCKET_ERROR) {
    DEBUG("send failed with error: " << WSAGetLastError(), LEVEL_ERROR);
    closesocket(ConnectSocket);
    WSACleanup();
  }

  DEBUG("Bytes Sent: " << iResult, LEVEL_DEBUG);

  closesocket(ConnectSocket);
}

std::string WINDOWS_Tcp_Transport::Receive() {
  return "";
}

WINDOWS_Tcp_Transport::WINDOWS_Tcp_Transport(const std::string &hostname, const std::string &port)
    : Transport(hostname, port) {
  // Initialize Winsock
  iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (iResult != 0) {
    DEBUG("WSAStartup failed with error: " << iResult, LEVEL_ERROR);
    exit(1);
  }

  ZeroMemory(&hints, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  // Resolve the server address and port
  iResult = getaddrinfo(hostname.c_str(), port.c_str(), &hints, &result);
  if (iResult != 0) {
    DEBUG("getaddrinfo failed with error: " << iResult, LEVEL_ERROR);
    WSACleanup();
  }
}

WINDOWS_Tcp_Transport::~WINDOWS_Tcp_Transport() {
  freeaddrinfo(result);
  WSACleanup();
}

}