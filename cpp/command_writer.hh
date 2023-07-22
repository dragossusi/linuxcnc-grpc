#pragma once

#include <iostream>

#include "linuxcnc.pb.h"

#include <cmd_msg.hh>

using linuxcnc::CncStatus;
using linuxcnc::JogAbsoluteRequest;
using linuxcnc::JogContinuousRequest;
using linuxcnc::JogIncrementalRequest;
using linuxcnc::JogStopRequest;
using linuxcnc::LoadTaskPlanRequest;
using linuxcnc::LoadToolTableRequest;
using linuxcnc::SendMdiCommandRequest;
using linuxcnc::SetAutoRequest;
using linuxcnc::SetBacklashRequest;
using linuxcnc::SetBlockDeleteRequest;
using linuxcnc::SetFeedHoldRequest;
using linuxcnc::SetFeedOverrideRequest;
using linuxcnc::SetFloodRequest;
using linuxcnc::SetMaxPositionPositionLimitRequest;
using linuxcnc::SetMinPositionPositionLimitRequest;
using linuxcnc::SetMistRequest;
using linuxcnc::SetOptionalStopRequest;
using linuxcnc::SetRapidOverrideRequest;
using linuxcnc::SetSpindleOverrideRequest;
using linuxcnc::SetSpindleRequest;
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

    int jogContinuos(const JogContinuousRequest *request);
    int jogIncremental(const JogIncrementalRequest *request);
    int jogAbsolute(const JogAbsoluteRequest *request);
    int jogStop(const JogStopRequest *request);

    int setMinPositionLimit(const SetMinPositionPositionLimitRequest *request);
    int setMaxPositionLimit(const SetMaxPositionPositionLimitRequest *request);
    int setBacklash(const SetBacklashRequest *request);

    int setFeedHold(const SetFeedHoldRequest *request);
    int loadTaskPlan(const LoadTaskPlanRequest *request);
    int loadToolTable(const LoadToolTableRequest *request);
    
    int sendMdiCommand(const SendMdiCommandRequest *request);

    int setAuto(const SetAutoRequest *request);
    int setBlockDelete(const SetBlockDeleteRequest *request);
    int setFeedOverride(const SetFeedOverrideRequest *request);
    int setFlood(const SetFloodRequest *request);
    int setMist(const SetMistRequest *request);
    int setOptionalStop(const SetOptionalStopRequest *request);
    int setRapidOverride(const SetRapidOverrideRequest *request);
    int setSpindle(const SetSpindleRequest *request);
    int setSpindleOverride(const SetSpindleOverrideRequest *request);
};
