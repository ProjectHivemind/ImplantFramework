#ifndef HIVEMIND_H
#define HIVEMIND_H
#include <string>

namespace hivemind_lib {
/**
 * @brief Enum for available modules
 */
enum ModuleEnum{
  All,
  Ping,
  CommandLine
};

/**
 * @brief Initialize the library.
 * @return Status.
 */
int Init();
/**
 * @brief Add function not found in a module to the library.
 * Stretch Goal TODO
 * @return Status.
 */
int AddFunction(void *);
//Register bot
/**
 * @brief Register the bot with the C&C server.
 * @param info The information needed to connect to the C&C.
 */
void RegisterBot();
//Start comms
/**
 * @brief Start the loop calling to the C&C.
 */
void BeginComms();

/**
 * @brief Unknown.
 */
void AddModule(ModuleEnum mod);
/**
 * @brief Use the TCP transport.
 * @return Status.
 */
int UseTCP();
/**
 * @brief Use the UDP transport
 * @return Status.
 */
int UseUDP();
/**
 * @brief User the ICMP transport.
 * @return Status.
 */
int UseICMP();
/**
 * @brief Initialize the communication method.
 * @param hostname The host to call back to.
 * @param port The port to call back to.
 * @return Status.
 */
int InitComms(std::string hostname, std::string port);

}
#endif
