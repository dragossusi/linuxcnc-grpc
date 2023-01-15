#include <any>
#include <iostream>
#include <config.h>
#include "status_reader.hh"

#include <emc_nml.hh>

static RCS_STAT_CHANNEL *cStat;
static EMC_STAT *status;

using linuxcnc::CncStatus;
using linuxcnc::status::ActiveCodes;
using linuxcnc::status::InterpreterState;
using linuxcnc::status::LengthUnit;
using linuxcnc::status::Position;
using linuxcnc::status::TaskExecState;
using linuxcnc::status::TaskMode;
using linuxcnc::status::TaskState;
using linuxcnc::status::TaskStatus;

TaskMode getTaskMode(EMC_TASK_MODE_ENUM mode)
{
    return TaskMode(mode - 1);
}

TaskState getTaskState(EMC_TASK_STATE_ENUM mode)
{
    return TaskState(mode - 1);
}

TaskExecState getTaskExecState(EMC_TASK_EXEC_ENUM mode)
{
    return TaskExecState(mode - 1);
}

InterpreterState getInterpreterState(EMC_TASK_INTERP_ENUM mode)
{
    return InterpreterState(mode - 1);
}

ActiveCodes *getActiveCodes(EMC_TASK_STAT task)
{
    ActiveCodes *codes = new ActiveCodes();

    // gCodes
    for (int i = 0; i < ACTIVE_G_CODES ; ++i)
    {
        codes->add_gcodes(task.activeGCodes[i]);
    }

    // mCodes
    for (int i = 0; i < ACTIVE_M_CODES; ++i)
    {
        codes->add_mcodes(task.activeMCodes[i]);
    }
    return codes;
}

LengthUnit getLengthUnit(CANON_UNITS units)
{
    switch (units)
    {
    case CANON_UNITS_INCHES:
        return LengthUnit::IN;
        break;
    case CANON_UNITS_MM:
        return LengthUnit::MM;
        break;
    case CANON_UNITS_CM:
        return LengthUnit::CM;
        break;

    default:
        std::cout << "Failed getLengthUnit" << std::endl;
        throw std::exception();
        break;
    }
}

Position *getPosition(EmcPose pose)
{
    Position *position = new Position();
    position->set_x(pose.tran.x);
    position->set_y(pose.tran.y);
    position->set_z(pose.tran.z);

    position->set_a(pose.a);
    position->set_b(pose.b);
    position->set_c(pose.c);

    position->set_u(pose.u);
    position->set_v(pose.v);
    position->set_w(pose.w);

    // todo i'm not sure what to do with this
    position->set_r(0.0);

    return position;
}

TaskStatus *getTaskStatus(EMC_TASK_STAT task)
{
    TaskStatus *status = new TaskStatus();
    status->set_taskmode(getTaskMode(task.mode));
    status->set_taskstate(getTaskState(task.state));
    status->set_execstate(getTaskExecState(task.execState));
    status->set_interpreterstate(getInterpreterState(task.interpState));
    status->set_subroutinecalllevel(task.callLevel);

    status->set_motionline(task.motionLine);
    status->set_currentline(task.currentLine);
    status->set_readline(task.readLine);

    status->set_isoptionalstopenabled(task.optional_stop_state);
    status->set_isblockdeleteenabled(task.block_delete_state);
    status->set_isdigitalinputtimeout(task.input_timeout);
    status->set_loadedfile(task.file);
    status->set_command(task.command);

    status->set_allocated_g5xoffset(getPosition(task.g5x_offset));
    status->set_g5xindex(task.g5x_index);
    status->set_allocated_g92offset(getPosition(task.g92_offset));

    status->set_rotationxy(task.rotation_xy);

    status->set_allocated_tooloffset(getPosition(task.toolOffset));

    status->set_allocated_activecodes(getActiveCodes(task));

    for (int setting : task.activeSettings)
    {
        status->add_activesettings(setting);
    }

    status->set_programunits(getLengthUnit(task.programUnits));

    status->set_intepretererrorcode(task.interpreter_errcode);
    status->set_istaskpaused(task.task_paused);

    status->set_delayleft(task.delayLeft);

    status->set_mdiinputqueue(task.queuedMDIcommands);

    // todo set fields
    return status;
}

StatusReader::StatusReader()
{
    cStat = new RCS_STAT_CHANNEL(emcFormat, "emcStatus", "xemc", EMC2_DEFAULT_NMLFILE);
    if (!cStat || !cStat->valid())
    {
        delete cStat;
        cStat = NULL;

        throw std::exception();
    }
    else
    {
        status = static_cast<EMC_STAT *>(cStat->get_address());
    }
}

int StatusReader::refreshStatus()
{
    if (!cStat || !cStat->valid())
        return -1;
    int rv = cStat->peek();

    if (!rv || rv == EMC_STAT_TYPE)
        return 0;
    return rv;
}

bool StatusReader::setStatus(CncStatus *cncStatus)
{
    TaskStatus *taskStatus = getTaskStatus(status->task);
    cncStatus->set_allocated_taskstatus(taskStatus);
    return true;
}