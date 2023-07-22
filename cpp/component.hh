
#include <map>

#include "linuxcnc.pb.h"

using linuxcnc::CreatePinRequest;
using linuxcnc::HalComponent;
using linuxcnc::HalPin;

class ComponentWithPins
{
private:
    std::map<std::string, HalPin> pins;

public:
    const HalComponent component;
    
    ComponentWithPins(HalComponent component);
    ~ComponentWithPins();

    HalPin createPin(std::string pin_id, CreatePinRequest request);
};
