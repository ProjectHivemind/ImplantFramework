//Interface to the hivemind_lib library eventually
namespace hivemind_lib {

struct CC_Info {
  int port = 0;
  const char *hostname{};
};

int Init();
//Add function to comms
int AddFunction(void *);
//Register bot
int RegisterBot(CC_Info info);
//Start comms
void BeginComms();
void AddModule();
int UseTCP();
int UseUDP();
int UseICMP();

}
