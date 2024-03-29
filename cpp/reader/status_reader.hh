#pragma once

#include <iostream>

#include "proto/linuxcnc/linuxcnc.pb.h"

using linuxcnc::CncStatus;

class StatusReader
{
public:
    StatusReader();
    int refreshStatus();
    bool setStatus(CncStatus *cncStatus);
};
