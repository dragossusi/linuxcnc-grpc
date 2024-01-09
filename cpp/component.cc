#include "component.hh"

ComponentWithPins::ComponentWithPins(HalComponent component) : component(component)
{
}

ComponentWithPins::~ComponentWithPins()
{
}

HalPin ComponentWithPins::createPin(
    std::string pin_id,
    CreatePinRequest request)
{

    auto existing = pins.find(pin_id);
    if (existing != pins.end())
    {
        return existing->second;
    }
    HalPin pin;

    //    pin.dir = request.dir();

    pin.set_component_id(component.component_id());
    pin.set_component_name(component.name());

    return pin;
}
