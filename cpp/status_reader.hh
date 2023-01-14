#pragma once

#include <any>

using std::any;

class StatusReader
{
public:
    StatusReader();
    int refreshStatus();
    any getStatus();
};
