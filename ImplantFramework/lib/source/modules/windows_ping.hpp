/** @file windows_ping.hpp
 * @brief Contains implementation for the PING module
 * @author Im_Adriano
 */
#ifndef HIVEMIND_IMPLANTFRAMEWORK_LIB_SOURCE_MODULES_WINDOWS_PING_HPP_
#define HIVEMIND_IMPLANTFRAMEWORK_LIB_SOURCE_MODULES_WINDOWS_PING_HPP_

#include "module.hpp"
#include "module_factory.hpp"

#include <winsock2.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#include <cstdio>
#include <utility>
#include <ws2tcpip.h>

namespace hivemind_lib {
/**
 * @brief Struct for the ping module, used to parse args sent to functions in that module.
 */
struct PingArgParse {
  std::string host{};
};

/**
 * @brief WINDOWS Implementation of the PING module.
 */
class WindowsPingModule : public Module {
 public:
  ModuleInfo Init() override {
    struct ModuleFuncInfo module_func_info;

    module_func_info.param_names.emplace_back("host");
    module_func_info.param_types.emplace_back("String");
    module_func_info.module_func_name = "PING";
    module_func_info.module_func_desc = "Function to Ping host";
    module_func_info.param_num = 1;

    this->mod_info_.module_funcs.push_back(module_func_info);
    this->mod_info_.module_name = "PING";
    this->mod_info_.module_desc = "A module to Ping hosts";

    std::function < std::string(std::string) > f = std::bind(&WindowsPingModule::Ping, this, std::placeholders::_1);

    this->func_map_.insert({"PING", f});
    this->timeout_map_.insert({"PING", 1});

    return this->mod_info_;
  }

  /**
   * @brief Module function to ping a host.
   * @param host The host to ping.
   * @return Result from ping.
   */
  std::string Ping(std::string host) {
    auto args = ParseData<PingArgParse>(std::move(host));

    HANDLE h_icmp_file;
    unsigned long ipaddr = INADDR_NONE;
    int dw_ret_val = 0;
    char send_data[32] = "Data Buffer";
    LPVOID reply_buffer = nullptr;
    int reply_size = 0;
    in_addr addr{};

    inet_pton(AF_INET, args.host.c_str(), &addr);

    if (addr.S_un.S_addr == INADDR_NONE) {
      DEBUG("No valid host given", LEVEL_ERROR);
      return "ERROR";
    }

    h_icmp_file = IcmpCreateFile();
    if (h_icmp_file == INVALID_HANDLE_VALUE) {
      DEBUG("Unable to open handle.", LEVEL_ERROR);
      DEBUG("IcmpCreatefile returned error: " << GetLastError(), LEVEL_ERROR);
      return "ERROR";
    }

    reply_size = sizeof(ICMP_ECHO_REPLY) + sizeof(send_data);
    reply_buffer = (VOID *) malloc(reply_size);
    if (reply_buffer == nullptr) {
      DEBUG("Unable to allocate memory", LEVEL_ERROR);
      return "ERROR";
    }

    dw_ret_val = IcmpSendEcho(h_icmp_file, addr.S_un.S_addr, send_data, sizeof(send_data),
                              nullptr, reply_buffer, reply_size, 1000);
    if (dw_ret_val != 0) {
      auto p_echo_reply = (PICMP_ECHO_REPLY) reply_buffer;
      struct in_addr reply_addr{};
      reply_addr.S_un.S_addr = p_echo_reply->Address;
      DEBUG("Sent icmp message to " << args.host, LEVEL_INFO);
      if (dw_ret_val > 1) {
        DEBUG("Received " << dw_ret_val << " icmp message responses", LEVEL_INFO);
        DEBUG("Information from the first response:", LEVEL_INFO);
      } else {
        DEBUG("Received " << dw_ret_val << " icmp message response", LEVEL_INFO);
        DEBUG("Information from this response:", LEVEL_INFO);
      }
      DEBUG("Received from " << inet_ntoa(reply_addr), LEVEL_INFO);
      DEBUG("Status = " << p_echo_reply->Status, LEVEL_INFO);
      DEBUG("Roundtrip time = " << p_echo_reply->RoundTripTime << " milliseconds", LEVEL_INFO);
    } else {
      DEBUG("Call to IcmpSendEcho failed.", LEVEL_ERROR);
      DEBUG("IcmpSendEcho returned error: " << GetLastError(), LEVEL_ERROR);
      return "ERROR";
    }
    return "PONG";
  }

  WindowsPingModule() = default;
};

REGISTER_MODULE_FACTORY(WindowsPingModule, "PingModule");

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PingArgParse, host);

}
#endif
