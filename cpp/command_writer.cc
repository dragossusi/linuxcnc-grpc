#include <iostream>
#include <sys/time.h>
#include "command_writer.hh"

#include <config.h>

#include <cmd_msg.hh>
#include <emc_nml.hh>

#define EMC_COMMAND_TIMEOUT 5.0 // how long to wait until timeout
#define EMC_COMMAND_DELAY 0.01  // seconds to sleep between checks

using linuxcnc::SetBacklashRequest;
using linuxcnc::SetMaxPositionPositionLimitRequest;
using linuxcnc::SetMinPositionPositionLimitRequest;

static RCS_CMD_CHANNEL *cCmd;
static RCS_STAT_CHANNEL *cStat;
static EMC_STAT *status;

void CommandWriter::sleep(double s)
{
    struct timeval tv;

    tv.tv_sec = s;
    tv.tv_usec = s * 1000000;
    select(0, NULL, NULL, NULL, &tv);
}

int CommandWriter::sendCommand(RCS_CMD_MSG &msg)
{
    if (cCmd->write(&msg))
        return -1;

    for (double end = 0.0; end < EMC_COMMAND_TIMEOUT; end += EMC_COMMAND_DELAY)
    {
        cStat->peek();

        if ((status->echo_serial_number - msg.serial_number) >= 0)
            return 0;
        sleep(EMC_COMMAND_DELAY);
    }
    return -1;
}

CommandWriter::CommandWriter()
{
    cCmd = new RCS_CMD_CHANNEL(emcFormat, "emcCommand", "xemc", EMC2_DEFAULT_NMLFILE);
    if (!cCmd || !cCmd->valid())
    {
        delete cCmd;
        cCmd = NULL;

        std::cout << "Command is not valid" << std::endl;
        throw std::exception();
    }
    cStat = new RCS_STAT_CHANNEL(emcFormat, "emcStatus", "xemc", EMC2_DEFAULT_NMLFILE);
    if (!cStat || !cStat->valid())
    {
        delete cCmd;
        delete cStat;
        cCmd = NULL;
        cStat = NULL;

        std::cout << "Command is not valid" << std::endl;
        throw std::exception();
    }
    status = static_cast<EMC_STAT *>(cStat->get_address());
}

int CommandWriter::setTaskMode(TaskMode taskMode)
{
    EMC_TASK_SET_MODE command;

    command.mode = (EMC_TASK_MODE_ENUM)(taskMode + 1);

    return sendCommand(command);
}

int CommandWriter::setTaskState(TaskState taskState)
{
    EMC_TASK_SET_STATE command;

    command.state = (EMC_TASK_STATE_ENUM)taskState;

    return sendCommand(command);
}

int CommandWriter::taskAbort()
{
    EMC_TASK_ABORT command;

    return sendCommand(command);
}

int CommandWriter::homeAxis(int jointNumber)
{
    EMC_JOINT_HOME command;

    command.joint = jointNumber;

    return sendCommand(command);
}

int CommandWriter::unhomeAxis(int jointNumber)
{
    EMC_JOINT_UNHOME command;

    command.joint = jointNumber;

    return sendCommand(command);
}

int CommandWriter::overrideLimits(int jointNumber)
{
    EMC_JOINT_OVERRIDE_LIMITS command;

    command.joint = jointNumber;

    return sendCommand(command);
}

int CommandWriter::jogContinuos(const JogContinuousRequest *request)
{
    EMC_JOG_CONT command;

    command.jjogmode = request->jog_mode();
    command.joint_or_axis = request->joint_or_axis();
    command.vel = request->velocity();

    return sendCommand(command);
}

int CommandWriter::jogIncremental(const JogIncrementalRequest *request)
{
    EMC_JOG_INCR command;

    command.jjogmode = request->jog_mode();
    command.joint_or_axis = request->joint_or_axis();
    command.vel = request->velocity();
    command.incr = request->stepsize();

    return sendCommand(command);
}

int CommandWriter::jogAbsolute(const JogAbsoluteRequest *request)
{
    EMC_JOG_ABS command;

    command.jjogmode = request->jog_mode();
    command.joint_or_axis = request->joint_or_axis();
    command.vel = request->velocity();
    command.pos = request->position();

    return sendCommand(command);
}

int CommandWriter::jogStop(const JogStopRequest *request)
{
    EMC_JOG_ABS command;

    command.jjogmode = request->jog_mode();
    command.joint_or_axis = request->joint_or_axis();

    return sendCommand(command);
}

int CommandWriter::setMinPositionLimit(const SetMinPositionPositionLimitRequest *request)
{

    EMC_JOINT_SET_MIN_POSITION_LIMIT command;

    command.joint = request->joint_num();
    command.limit = request->limit();

    return sendCommand(command);
}

int CommandWriter::setMaxPositionLimit(const SetMaxPositionPositionLimitRequest *request)
{
    EMC_JOINT_SET_MAX_POSITION_LIMIT command;

    command.joint = request->joint_num();
    command.limit = request->limit();

    return sendCommand(command);
}

int CommandWriter::setBacklash(const SetBacklashRequest *request)
{
    EMC_JOINT_SET_BACKLASH command;

    command.joint = request->joint_num();
    command.backlash = request->backlash();

    return sendCommand(command);
}

int CommandWriter::setFeedHold(const SetFeedHoldRequest *request)
{
    EMC_TRAJ_SET_FH_ENABLE command;

    command.mode = request->mode();

    return sendCommand(command);
}

int CommandWriter::loadTaskPlan(const LoadTaskPlanRequest *request)
{
    EMC_TASK_PLAN_CLOSE closeCommand;
    EMC_TASK_PLAN_OPEN openCommand;

    sendCommand(closeCommand);
    strcpy(openCommand.file, request->file_name().c_str());

    return sendCommand(openCommand);
}

int CommandWriter::loadToolTable(const LoadToolTableRequest *request)
{
    // todo
    return 0;
}

int CommandWriter::sendMdiCommand(const SendMdiCommandRequest *request)
{
    EMC_TASK_PLAN_EXECUTE command;

    strcpy(command.command, request->command().c_str());

    return sendCommand(command);
}

int CommandWriter::setAuto(const SetAutoRequest *request)
{
    // todo
    return 0;
}

int CommandWriter::setBlockDelete(const SetBlockDeleteRequest *request)
{
    EMC_TASK_PLAN_SET_BLOCK_DELETE command;

    if (request->enabled())
        command.state = 1;
    else
        command.state = 0;

    return sendCommand(command);
}

int CommandWriter::setFeedOverride(const SetFeedOverrideRequest *request)
{
    EMC_TRAJ_SET_SCALE command;

    command.scale = request->rate();

    return sendCommand(command);
}

int CommandWriter::setFlood(const SetFloodRequest *request)
{
    if (request->enabled())
    {
        EMC_COOLANT_FLOOD_ON command;

        return sendCommand(command);
    }
    else
    {
        EMC_COOLANT_FLOOD_OFF command;

        return sendCommand(command);
    }
}

int CommandWriter::setMist(const SetMistRequest *request)
{
    if (request->enabled())
    {
        EMC_COOLANT_MIST_ON command;

        return sendCommand(command);
    }
    else
    {
        EMC_COOLANT_MIST_OFF command;

        return sendCommand(command);
    }
}

int CommandWriter::setOptionalStop(const SetOptionalStopRequest *request)
{
    EMC_TASK_PLAN_SET_OPTIONAL_STOP command;

    command.state = request->stop();

    return sendCommand(command);
}

int CommandWriter::setRapidOverride(const SetRapidOverrideRequest *request)
{
    EMC_TRAJ_SET_RAPID_SCALE command;

    command.scale = request->rate();

    return sendCommand(command);
}

int CommandWriter::setSpindle(const SetSpindleRequest *request)
{
    if (request->enabled())
    {
        EMC_SPINDLE_ON command;

        command.speed = request->direction() * request->speed();
        command.spindle = 0;

        return sendCommand(command);
    }
    else
    {
        EMC_SPINDLE_OFF command;

        command.spindle = 0;

        return sendCommand(command);
    }
}

int CommandWriter::setSpindleOverride(const SetSpindleOverrideRequest *request)
{
    EMC_TRAJ_SET_SPINDLE_SCALE command;

    command.spindle = 0;
    command.scale = request->rate();

    return sendCommand(command);
}
