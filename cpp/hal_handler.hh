#include <map>
#include <vector>
#include "linuxcnc.pb.h"

using linuxcnc::CreateComponentRequest;
using linuxcnc::HalComponent;

class HalHandler
{
private:
    std::map<std::string, HalComponent> componentsMap;

public:
    HalHandler();
    std::vector<HalComponent> getHalComponents();
    int createHalComponent(const CreateComponentRequest *request, HalComponent *response);
};
