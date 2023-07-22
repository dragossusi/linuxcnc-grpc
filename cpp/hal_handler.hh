#include <map>
#include <vector>

#include "linuxcnc.pb.h"
#include "component.hh"

using linuxcnc::CreateComponentRequest;
using linuxcnc::HalComponent;

class HalHandler
{
private:
    std::map<std::string, ComponentWithPins> componentsMap;

public:
    HalHandler();
    std::vector<HalComponent> getHalComponents();
    int createHalComponent(const CreateComponentRequest *request, HalComponent *response);
};
