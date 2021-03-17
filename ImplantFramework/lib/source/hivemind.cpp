#include "hivemind.h"

#include <memory>
#include "iostream"
#include "logic_controller.hpp"

namespace hivemind_lib {
std::unique_ptr<LogicController> controller;

void Init() {
  controller = std::make_unique<LogicController>();
}

void RegisterBot() {
  if (!controller) {
    std::cerr << "Call Init first!" << std::endl;
    return;
  }
  controller->RegisterBot();
  if (controller->HasError()) {
    std::cerr << "Error in RegisterBot. Did you call InitComms?" << std::endl;
  }
}

void BeginComms() {
  if (!controller) {
    std::cerr << "Call Init first!" << std::endl;
    return;
  }
  controller->BeginComms();
  if (controller->HasError()) {
    std::cerr << "Error in BeginComms. Did you call RegisterBot?" << std::endl;
  }
}

void InitComms(const std::string& hostname, const std::string &port) {
  if (!controller) {
    std::cerr << "Call Init first!" << std::endl;
    return;
  }
  controller->InitComms(hostname, port);
  if (controller->HasError()) {
    std::cerr << "Make sure to add a transport type before calling InitComms" << std::endl;
  }
}

void AddModule(const std::string& mod) {
  if (!controller) {
    std::cerr << "Call Init first!" << std::endl;
    return;
  }
  controller->AddModule(mod);
}

void AddTransport(const std::string& transport) {
  if (!controller) {
    std::cerr << "Call Init first!" << std::endl;
    return;
  }
  controller->SetTransportMethod(transport);
}
}

