#include <any>
#include <emc_nml.hh>
#include <config.h>
#include "status_reader.hh"

static RCS_STAT_CHANNEL *cStat;
static EMC_STAT *status;

using std::any;

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

any StatusReader::getStatus()
{
    any response = status;
    return response;
}