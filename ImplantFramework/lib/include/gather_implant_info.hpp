/** @file gather_system_info.hpp
 * @brief Defines the functions needed to gather system information.
 * @author f1rehaz4rd
 */

#ifndef HIVEMIND_IMPLANTFRAMEWORK_LIB_INCLUDE_GATHER_IMPLANT_INFO_H_
#define HIVEMIND_IMPLANTFRAMEWORK_LIB_INCLUDE_GATHER_IMPLANT_INFO_H_

#include <vector>
#include <string>

namespace hivemind_lib {

class Gather_Info {
 public:
  /**
   * @brief
   * @return
   */
  static std::string GetPrimaryIP();

  /**
   * @brief
   * @return
   */
  static std::string GetHostname();

  /**
   * @brief
   * @return
   */
  static std::string GetMACAddr();

  /**
   * @brief
   * @return
   */
  static std::vector<std::string> GetOtherIPs();
};

}

#endif //HIVEMIND_IMPLANTFRAMEWORK_LIB_INCLUDE_GATHER_IMPLANT_INFO_H_
