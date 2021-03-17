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

void UseTcp() {
  if (!controller) {
    std::cerr << "Call Init first!" << std::endl;
    return;
  }
  controller->SetTransportMethod(TCP);
}

void UseUdp() {
  if (!controller) {
    std::cerr << "Call Init first!" << std::endl;
    return;
  }
  controller->SetTransportMethod(UDP);
}

void UseIcmp() {
  if (!controller) {
    std::cerr << "Call Init first!" << std::endl;
    return;
  }
  controller->SetTransportMethod(ICMP);
}

void InitComms(std::string hostname, std::string port) {
  if (!controller) {
    std::cerr << "Call Init first!" << std::endl;
    return;
  }
  controller->InitComms(std::move(hostname), std::move(port));
  if (controller->HasError()) {
    std::cerr << "Make sure to set transport type before calling InitComms" << std::endl;
  }
}

void AddModule(ModuleEnum mod) {
  if (!controller) {
    std::cerr << "Call Init first!" << std::endl;
    return;
  }
  controller->AddModule(mod);
}
}

