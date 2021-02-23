/** @file comms.hpp
 * @brief Defines the action structs used for communication.
 * @author Im_Adriano
 */
#ifndef HIVEMIND_IMPLANTFRAMEWORK_LIB_INCLUDE_COMMS_HPP_
#define HIVEMIND_IMPLANTFRAMEWORK_LIB_INCLUDE_COMMS_HPP_

#include <string>
#include <vector>
#include "module.hpp"
#include "json.hpp"

/** @namespace hivemind_lib
 * @brief The Hivemind library
 */
namespace hivemind_lib {

enum PacketType {
  ERROR_CODE = -1,
  NO_ACTION = 0,
  ACTION_REQUEST = 1,
  ACTION_CODE = 2,
  ACTION_RESPONSE_CODE = 3,
  REGISTRATION_REQUEST_CODE = 4,
  REGISTRATION_RESPONSE_CODE = 5
};

enum ErrorNum {
  NOT_REGISTERED = -1,
  UNKNOWN_MODULE = -2,
  UNKNOWN_MODULE_FUNCTION = -3,
  MISSING_REQUIRED_DATA = -4,
  MODULE_TIMEOUT = -5,
  DUPLICATE_REGISTRATION = -6,
  UNKNOWN_ERROR = -7
};

struct ImplantInfo {
  std::string UUID;
  std::string primaryIP;
};

struct Action {
  std::string actionId;
  std::string module;
  std::string moduleFunc;
  std::string arguments;
};

struct ActionResponse {
  std::string actionId;
  std::string response;
};

struct Packet {
  std::string fingerprint;
  ImplantInfo implantInfo;
  PacketType packetType;
  int numLeft;
  std::string data;
};

struct Error {
  std::string actionId;
  ErrorNum errorNum;
};

struct RegistrationRequest {
  std::string IP;
  std::string implantName;
  std::string implantVersion;
  std::string hostname;
  std::string MAC;
  std::vector<std::string> otherIPs;
  std::string OS;
  std::vector<ModuleInfo> supportedModules;
};

struct RegistrationResponse {
  std::string UUID;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ImplantInfo, UUID, primaryIP);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ActionResponse, actionId, response);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Action, actionId, module, moduleFunc, arguments);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Error, actionId, errorNum);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RegistrationRequest,
                                   IP,
                                   implantName,
                                   implantVersion,
                                   hostname,
                                   MAC,
                                   otherIPs,
                                   OS,
                                   supportedModules);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Packet, fingerprint, implantInfo, packetType, numLeft, data);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RegistrationResponse, UUID);

}

#endif
