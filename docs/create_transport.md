Creating a transport is a straight forward process.
All of your code for this module will be self contained in a single header.

This guide assumes you already have a development environment setup following [this](prequisites.md) page.

Now create a file in the `ImplantFramework/lib/source/transports` folder.
Your file must follow the naming convention `<target os>_<name of your transport>.hpp`.
For example `windows_udp.hpp` or `linux_udp.hpp`.

Next place this starter module code in your file:

```cpp
/** @file target_example.hpp
 * @brief Contains implementation for the example transport
 * @author My Name
 */
#ifndef HIVEMIND_IMPLANTFRAMEWORK_LIB_SOURCE_TRANSPORTS_TARGET_EXAMPLE_HPP_
#define HIVEMIND_IMPLANTFRAMEWORK_LIB_SOURCE_TRANSPORTS_TARGET_EXAMPLE_HPP_
#include "transport.hpp"
#include "transport_factory.hpp"

/** @namespace hivemind_lib
 * @brief The Hivemind library
 */
namespace hivemind_lib {

/**
 * @brief Target implementation of the Example transport.
 */
class TargetExampleTransport : public Transport {
 public:
  std::string SendAndReceive(std::string data) {
    return "";
  }

  void Send(std::string data) {
    return;
  }

  std::string Receive() {
    return "";
  }

  TargetExampleTransport(const std::string &hostname, const std::string &port)
      : Transport(hostname, port) {
   
  }
};

REGISTER_TRANSPORT_FACTORY(TargetExampleTransport, "EXAMPLE");

}
#endif
```

1. First rename all the `Target` and `Example` instances with the target and name of your transport. 
1. Next implement the `SendAndReceive`, `Send` and constructor for your transport.
1. `SendAndReceive` first sends the given data then listens for a response until a certain condition is met like a connection close for TCP or a sentient value for UDP.
1. `Send` sends the given data the returns. Add to the constructor as necessary. 
  
Once these are implemented rerun the cmake/make and you have created a transport!