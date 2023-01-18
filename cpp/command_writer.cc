#include <iostream>
#include <sys/time.h>
#include "command_writer.hh"

#include <config.h>

#include <cmd_msg.hh>
#include <emc_nml.hh>

#define EMC_COMMAND_TIMEOUT 5.0 // how long to wait until timeout
#define EMC_COMMAND_DELAY 0.01  // seconds to sleep between checks

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

        std::cout<<"Command is not valid"<<std::endl;
        throw std::exception();
    }
    cStat = new RCS_STAT_CHANNEL(emcFormat, "emcStatus", "xemc", EMC2_DEFAULT_NMLFILE);
    if (!cStat || !cStat->valid())
    {
        delete cCmd;
        delete cStat;
        cCmd = NULL;
        cStat = NULL;

        std::cout<<"Command is not valid"<<std::endl;
        throw std::exception();
    }
    status = static_cast<EMC_STAT *>(cStat->get_address());
}

int CommandWriter::setTaskMode(TaskMode taskMode)
{
    EMC_TASK_SET_MODE command;

    command.mode = (EMC_TASK_MODE_ENUM) taskMode;

    return sendCommand(command);
}
