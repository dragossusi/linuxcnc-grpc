#pragma once

#include <iostream>

#include "linuxcnc.pb.h"

using linuxcnc::CncStatus;

class StatusReader
{
public:
    StatusReader();
    int refreshStatus();
    bool setStatus(CncStatus *cncStatus);
};
