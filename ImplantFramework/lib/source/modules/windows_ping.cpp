#include "module.hpp"
#include "windows.hpp"

#include <winsock2.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#include <cstdio>

namespace hivemind_lib {

std::string WINDOWS_Ping_Module::ping(std::string host) {
  HANDLE hIcmpFile;
  unsigned long ipaddr = INADDR_NONE;
  int dwRetVal = 0;
  char SendData[32] = "Data Buffer";
  LPVOID ReplyBuffer = nullptr;
  int ReplySize = 0;

  ipaddr = inet_addr(host.c_str());
  if (ipaddr == INADDR_NONE) {
    DEBUG("No valid host given", LEVEL_ERROR);
  }

  hIcmpFile = IcmpCreateFile();
  if (hIcmpFile == INVALID_HANDLE_VALUE) {
    DEBUG("Unable to open handle.", LEVEL_ERROR);
    DEBUG("IcmpCreatefile returned error: " << GetLastError(), LEVEL_ERROR);
  }

  ReplySize = sizeof(ICMP_ECHO_REPLY) + sizeof(SendData);
  ReplyBuffer = (VOID *) malloc(ReplySize);
  if (ReplyBuffer == nullptr) {
    DEBUG("Unable to allocate memory", LEVEL_ERROR);
  }

  dwRetVal = IcmpSendEcho(hIcmpFile, ipaddr, SendData, sizeof(SendData),
                          nullptr, ReplyBuffer, ReplySize, 1000);
  if (dwRetVal != 0) {
    auto pEchoReply = (PICMP_ECHO_REPLY) ReplyBuffer;
    struct in_addr ReplyAddr{};
    ReplyAddr.S_un.S_addr = pEchoReply->Address;
    DEBUG("Sent icmp message to " << host, LEVEL_INFO);
    if (dwRetVal > 1) {
      DEBUG("Received " << dwRetVal << " icmp message responses", LEVEL_INFO);
      DEBUG("Information from the first response:", LEVEL_INFO);
    } else {
      DEBUG("Received " << dwRetVal << " icmp message response", LEVEL_INFO);
      DEBUG("Information from this response:", LEVEL_INFO);
    }
    DEBUG("Received from " << inet_ntoa(ReplyAddr), LEVEL_INFO);
    DEBUG("Status = " << pEchoReply->Status, LEVEL_INFO);
    DEBUG("Roundtrip time = " << pEchoReply->RoundTripTime << " milliseconds", LEVEL_INFO);
  } else {
    DEBUG("Call to IcmpSendEcho failed.", LEVEL_ERROR);
    DEBUG("IcmpSendEcho returned error: " << GetLastError(), LEVEL_ERROR);
  }
  return "";
}

ModuleInfo WINDOWS_Ping_Module::init() {
  struct ModuleFuncInfo module_func_info;

  module_func_info.paramNames.emplace_back("Host");
  module_func_info.paramTypes.emplace_back("STRING");
  module_func_info.moduleFuncName = "PING";
  module_func_info.paramNum = 1;

  this->modInfo.moduleFuncs.push_back(module_func_info);
  this->modInfo.moduleName = "PING";
  this->modInfo.moduleDesc = "A module to ping hosts";

  std::function < std::string(std::string) > f = std::bind(&WINDOWS_Ping_Module::ping, this, std::placeholders::_1);

  this->funcMap.insert({"PING", f});
  this->timeoutMap.insert({"PING", 60});

  return this->modInfo;
}

WINDOWS_Ping_Module::WINDOWS_Ping_Module() = default;
}
