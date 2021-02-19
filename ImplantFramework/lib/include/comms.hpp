/** @file comms.hpp
 * @brief Defines the action structs used for communication.
 * @author Im_Adriano
 */
#ifndef COMMS_H
#define COMMS_H

#include <string>
#include <vector>
#include "module.hpp"
#include "json.hpp"

/** @namespace hivemind_lib
 * @brief The Hivemind library
 */
namespace hivemind_lib {

enum PacketType {
  ErrorCode = -1,
  NoAction = 0,
  ActionRequest = 1,
  ActionCode = 2,
  ActionResponseCode = 3,
  RegistrationRequestCode = 4,
  RegistrationResponseCode = 5
};

enum ErrorNum {
  NotRegistered = -1,
  UnknownModule = -2,
  UnknownModuleFunction = -3,
  MissingRequiredData = -4,
  ModuleTimeout = -5,
  DuplicateRegistration = -6,
  UnknownError = -7
};

struct ImplantInfo {
  std::string UUID;
  std::string primaryIP;
};

struct Action {
  int actionId;
  std::string module;
  std::string moduleFunc;
  std::vector<std::string> arguments;
};

struct ActionResponse {
  int actionId;
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
