#include <iostream>
#include <config.h>
#include "status_reader.hh"

#include <emc_nml.hh>

static RCS_STAT_CHANNEL *cStat;
static EMC_STAT *status;

using linuxcnc::CncStatus;
using linuxcnc::status::ActiveCodes;
using linuxcnc::status::AuxStatus;
using linuxcnc::status::AxisStatus;
using linuxcnc::status::CoolantStatus;
using linuxcnc::status::InterpreterState;
using linuxcnc::status::IoStatus;
using linuxcnc::status::JointStatus;
using linuxcnc::status::LengthUnit;
using linuxcnc::status::LubeStatus;
using linuxcnc::status::MotionStatus;
using linuxcnc::status::Position;
using linuxcnc::status::SpindleStatus;
using linuxcnc::status::TaskExecState;
using linuxcnc::status::TaskMode;
using linuxcnc::status::TaskState;
using linuxcnc::status::TaskStatus;
using linuxcnc::status::ToolStatus;
using linuxcnc::status::TrajectoryMode;
using linuxcnc::status::TrajectoryStatus;

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
    for (int i = 0; i < ACTIVE_G_CODES; ++i)
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

ToolStatus *getToolStatus(EMC_TOOL_STAT tool)
{
    ToolStatus *status = new ToolStatus();
    status->set_pocketprepared(tool.pocketPrepped);
    status->set_toolinspindle(tool.toolInSpindle);
    status->set_toolfrompocket(tool.toolInSpindle);
    return status;
}

CoolantStatus *getCoolantStatus(EMC_COOLANT_STAT coolant)
{
    CoolantStatus *status = new CoolantStatus();

    status->set_mist((bool)coolant.mist);
    status->set_flood((bool)coolant.flood);

    return status;
}

AuxStatus *getAuxStatus(EMC_AUX_STAT aux)
{
    AuxStatus *status = new AuxStatus();

    status->set_estop((bool)aux.estop);

    return status;
}

LubeStatus *getLubeStatus(EMC_LUBE_STAT lube)
{
    LubeStatus *status = new LubeStatus();

    status->set_on(lube.on);
    status->set_level(lube.level);

    return status;
}

IoStatus *getIoStatus(EMC_IO_STAT io)
{
    IoStatus *status = new IoStatus();

    status->set_cycletime(io.cycleTime);
    status->set_reason(io.reason);
    status->set_fault(io.fault);
    status->set_allocated_toolstatus(getToolStatus(io.tool));
    status->set_allocated_coolantstatus(getCoolantStatus(io.coolant));
    status->set_allocated_auxstatus(getAuxStatus(io.aux));
    status->set_allocated_lubestatus(getLubeStatus(io.lube));

    return status;
}

TrajectoryMode getTrajectoryMode(EMC_TRAJ_MODE_ENUM mode)
{
    return TrajectoryMode(mode - 1);
}

TrajectoryStatus *getTrajectoryStatus(EMC_TRAJ_STAT traj)
{
    TrajectoryStatus *status = new TrajectoryStatus();

    status->set_linear_units(traj.linearUnits);
    status->set_angular_units(traj.angularUnits);
    status->set_cycle_time(traj.cycleTime);
    status->set_joints(traj.joints);
    status->set_spindles(traj.spindles);
    status->set_axis_mask(traj.axis_mask);
    status->set_mode(getTrajectoryMode(traj.mode));
    status->set_enabled(traj.enabled);

    status->set_inposition(traj.inpos);

    status->set_queue(traj.queue);

    status->set_activequeue(traj.activeQueue);
    status->set_queuefull(traj.queueFull);
    status->set_id(traj.id);
    status->set_paused(traj.paused);
    status->set_scale(traj.scale);
    status->set_rapid_scale(traj.rapid_scale);

    status->set_allocated_position(getPosition(traj.position));
    status->set_allocated_actualposition(getPosition(traj.actualPosition));

    status->set_velocity(traj.velocity);
    status->set_acceleration(traj.acceleration);

    status->set_maxvelocity(traj.maxVelocity);
    status->set_maxacceleration(traj.maxAcceleration);

    status->set_allocated_probedposition(getPosition(traj.probedPosition));
    status->set_probe_tripped(traj.probe_tripped);
    status->set_probing(traj.probing);
    status->set_probeval(traj.probeval);

    status->set_kinematics_type(traj.kinematics_type);
    status->set_motion_type(traj.motion_type);

    status->set_distance_to_go(traj.distance_to_go);
    status->set_allocated_dtg(getPosition(traj.dtg));

    status->set_current_vel(traj.current_vel);

    status->set_feed_override_enabled(traj.feed_hold_enabled);
    status->set_adaptive_feed_enabled(traj.adaptive_feed_enabled);
    status->set_feed_hold_enabled(traj.feed_hold_enabled);

    return status;
}

void fillJointStatus(JointStatus *status, EMC_JOINT_STAT joint)
{
    status->set_joint_type(joint.jointType);

    status->set_units(joint.units);
    status->set_backlash(joint.backlash);

    status->set_min_position_limit(joint.minPositionLimit);
    status->set_max_position_limit(joint.maxPositionLimit);

    status->set_min_following_error(joint.minFerror);
    status->set_max_following_error(joint.maxFerror);

    status->set_current_following_error(joint.ferrorCurrent);
    status->set_current_following_error_high_mark(joint.ferrorHighMark);

    status->set_commanded_output_position(joint.output);

    status->set_current_input_position(joint.input);
    status->set_current_velocity(joint.velocity);

    status->set_in_position(joint.inpos);

    status->set_homing(joint.homing);
    status->set_homed(joint.homed);

    status->set_amp_fault(joint.fault);
    status->set_enabled(joint.enabled);

    status->set_min_soft_limit_exceeded(joint.minSoftLimit);
    status->set_max_soft_limit_exceeded(joint.maxSoftLimit);

    status->set_overriding_limits(joint.overrideLimits);
}

void fillSpindleStatus(SpindleStatus *status, EMC_SPINDLE_STAT spindle)
{
    status->set_speed(spindle.speed);
    status->set_spindle_scale(spindle.spindle_scale);

    status->set_css_maximum(spindle.css_maximum);
    status->set_css_factor(spindle.css_factor);

    status->set_state(spindle.state);
    status->set_direction(spindle.direction);
    status->set_brake(spindle.brake);
    status->set_increasing(spindle.increasing);

    status->set_enabled(spindle.enabled);

    status->set_orient_state(spindle.orient_state);
    status->set_orient_fault(spindle.orient_fault);

    status->set_spindle_override_enabled(spindle.spindle_override_enabled);
    status->set_homed(spindle.homed);
}

MotionStatus *getMotionStatus(EMC_MOTION_STAT motion)
{
    MotionStatus *status = new MotionStatus();

    status->set_allocated_trajectory_status(getTrajectoryStatus(motion.traj));

    for (auto joint : motion.joint)
    {
        auto jointStatus = status->add_joint_status();
        fillJointStatus(jointStatus, joint);
    }

    for (EMC_AXIS_STAT axis : motion.axis)
    {
        AxisStatus *axisStatus = status->add_axis_status();
        axisStatus->set_minpositionlimit(axis.minPositionLimit);
        axisStatus->set_maxpositionlimit(axis.maxPositionLimit);
        axisStatus->set_velocity(axis.velocity);
    }

    for (auto spindle : motion.spindle)
    {
        auto spindleStatus = status->add_spindle_status();
        fillSpindleStatus(spindleStatus, spindle);
    }

    // todo spindle

    // synch di
    for (int value : motion.synch_di)
    {
        status->add_synch_di(value);
    }

    // synch do
    for (int value : motion.synch_do)
    {
        status->add_synch_do(value);
    }

    // analog input
    for (double value : motion.analog_input)
    {
        status->add_analog_input(value);
    }

    // analog output
    for (double value : motion.analog_output)
    {
        status->add_analog_output(value);
    }

    // misc error
    for (int value : motion.misc_error)
    {
        status->add_misc_error(value);
    }

    status->set_debug(motion.debug);

    status->set_on_soft_limit(motion.on_soft_limit);
    status->set_external_offsets_applied(motion.external_offsets_applied);
    status->set_allocated_eoffset_pose(getPosition(motion.eoffset_pose));
    status->set_numextrajoints(motion.numExtraJoints);
    status->set_jogging_active(motion.jogging_active);

    return status;
}

// status reader
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
    IoStatus *ioStatus = getIoStatus(status->io);
    MotionStatus *motionStatus = getMotionStatus(status->motion);
    cncStatus->set_allocated_taskstatus(taskStatus);
    cncStatus->set_allocated_iostatus(ioStatus);
    cncStatus->set_allocated_motionstatus(motionStatus);
    return true;
}