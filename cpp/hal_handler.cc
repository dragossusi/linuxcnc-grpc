#include "hal_handler.hh"

#include "linuxcnc.pb.h"

#include <hal.h>

using linuxcnc::HalComponent;

HalHandler::HalHandler()
{
}

std::vector<HalComponent> HalHandler::getHalComponents()
{
    std::vector<HalComponent> components;
    for (auto const &iterator : componentsMap)
    {
        auto component = iterator.second.component;
        components.push_back(component);
    }
    return components;
}

int HalHandler::createHalComponent(const CreateComponentRequest *request, HalComponent *response)
{
    auto name = request->name();

    auto existing = componentsMap.find(name);
    if (existing != componentsMap.end())
    {
        return 0;
    }

    int result = hal_init(name.c_str());

    if (result <= 0)
    {
        return -1;
    }

    HalComponent *component = new HalComponent();

    component->set_name(name);
    component->set_component_id(result);

    auto pair = std::pair(name, *component);
    componentsMap.insert(pair);

    response->CopyFrom(*component);

    return 1;
}
