#ifndef HIVEMIND_IMPLANTFRAMEWORK_LIB_INCLUDE_MODULE_ARG_PARSE_HPP_
#define HIVEMIND_IMPLANTFRAMEWORK_LIB_INCLUDE_MODULE_ARG_PARSE_HPP_
#include <string>
#include "json.hpp"

namespace hivemind_lib {

struct PingArgParse {
  std::string host{};
};

template<typename structType>
structType ParseData(std::string data) {
  nlohmann::json extract = nlohmann::json::parse(data);
  return extract.get<structType>();
}

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PingArgParse, host);

}

#endif
