#include <string>

namespace hivemind_lib {

struct CC_Info {
  int port = 0;
  const char *hostname{};
};

int Init();
//Add function to comms
int AddFunction(void *);
//Register bot
void RegisterBot(CC_Info info);
//Start comms
void BeginComms();
void AddModule();
int UseTCP();
int UseUDP();
int UseICMP();
int InitComms(std::string hostname, std::string port);

}
