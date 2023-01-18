#pragma once

#include <iostream>

#include "proto/linuxcnc.pb.h"

#include <cmd_msg.hh>

using linuxcnc::CncStatus;
using linuxcnc::status::TaskMode;

class CommandWriter
{

private:
    void sleep(double s);
    int sendCommand(RCS_CMD_MSG& msg);
public:
    CommandWriter();
    int setTaskMode(TaskMode taskMode);
};
