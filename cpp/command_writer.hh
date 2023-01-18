#pragma once

#include <iostream>

#include "proto/linuxcnc.pb.h"

#include <cmd_msg.hh>

using linuxcnc::CncStatus;
using linuxcnc::JogAbsoluteRequest;
using linuxcnc::JogContinuousRequest;
using linuxcnc::JogIncrementalRequest;
using linuxcnc::JogStopRequest;
using linuxcnc::status::TaskMode;
using linuxcnc::status::TaskState;

class CommandWriter
{

private:
    void sleep(double s);
    int sendCommand(RCS_CMD_MSG &msg);

public:
    CommandWriter();
    int setTaskMode(TaskMode taskMode);
    int setTaskState(TaskState taskState);
    int taskAbort();

    int homeAxis(int jointNumber);
    int unhomeAxis(int jointNumber);

    int overrideLimits(int jointNumber);

    int jogContinuos(JogContinuousRequest *request);
    int jogIncremental(JogIncrementalRequest *request);
    int jogAbsolute(JogAbsoluteRequest *request);
    int jogStop(JogStopRequest *request);
};
