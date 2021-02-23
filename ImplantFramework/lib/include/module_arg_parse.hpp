#ifndef HIVEMIND_IMPLANTFRAMEWORK_LIB_INCLUDE_MODULE_ARG_PARSE_HPP_
#define HIVEMIND_IMPLANTFRAMEWORK_LIB_INCLUDE_MODULE_ARG_PARSE_HPP_
#include <string>
#include "json.hpp"

namespace hivemind_lib {

/**
 * @brief Struct for the ping module, used to parse args sent to functions in that module.
 */
struct PingArgParse {
  std::string host{};
};

/**
 * @brief Parses json from string to a struct, used in module functions.
 * @tparam structType The struct type to fill out and return.
 * @param data The json to parse.
 * @return The struct filled with data from the parsed json.
 */
template<typename structType>
structType ParseData(std::string data) {
  nlohmann::json extract = nlohmann::json::parse(data);
  return extract.get<structType>();
}

/**
 * @brief Generate json parsing functions for struct.
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PingArgParse, host);

}

#endif
