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
  std::string uuid;
  std::string primary_ip;
};

/**
 * @brief Struct used to parse and action received from the teamserver.
 */
struct Action {
  std::string action_id;
  std::string module;
  std::string module_func;
  std::string arguments;
};

/**
 * @brief Struct used to send a response to the teamserver.
 */
struct ActionResponse {
  std::string action_id;
  std::string response;
};

/**
 * @brief Struct used to parse/create packets received and sent to the teamserver.
 */
struct Packet {
  std::string fingerprint;
  ImplantInfo implant_info;
  PacketType packet_type;
  int num_left;
  std::string data;
};

/**
 * @brief Struct to parse error packet from teamserver.
 */
struct Error {
  std::string action_id;
  ErrorNum error_num;
};

/**
 * @brief Struct to create a registration request to register the bot with the teamserver.
 */
struct RegistrationRequest {
  std::string ip;
  std::string implant_name;
  std::string implant_version;
  std::string hostname;
  std::string mac;
  std::vector<std::string> other_ips;
  std::string os;
  std::vector<ModuleInfo> supported_modules;
};

/**
 * @brief Used to parse the registration response sent by the teamserver.
 */
struct RegistrationResponse {
  std::string uuid;
};

/**
 * @brief Generate json parsing functions for struct.
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ImplantInfo, uuid, primary_ip);

/**
 * @brief Generate json parsing functions for struct.
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ActionResponse, action_id, response);

/**
 * @brief Generate json parsing functions for struct.
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Action, action_id, module, module_func, arguments);

/**
 * @brief Generate json parsing functions for struct.
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Error, action_id, error_num);

/**
 * @brief Generate json parsing functions for struct.
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RegistrationRequest,
                                   ip,
                                   implant_name,
                                   implant_version,
                                   hostname,
                                   mac,
                                   other_ips,
                                   os,
                                   supported_modules);

/**
 * @brief Generate json parsing functions for struct.
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Packet, fingerprint, implant_info, packet_type, num_left, data);

/**
 * @brief Generate json parsing functions for struct.
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RegistrationResponse, uuid);

}

#endif
