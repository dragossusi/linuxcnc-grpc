#include <iostream>
#include <stat_msg.hh>
#include <cmd_msg.hh>
#include <emc_nml.hh>
#include <nml.hh>
#include <nml_oi.hh>
#include <stdio.h>
#include <cstring>
#include <config.h>

#include "error_reader.hh"

static NML *ec;

ErrorReader::ErrorReader()
{
    const char *nmlFile = EMC2_DEFAULT_NMLFILE;

    ec = new NML(emcFormat, "emcError", "xemc", nmlFile);

    if (!ec || !ec->valid())
    {
        delete ec;
        ec = NULL;

        throw std::exception();
    }
    if (ec->error_type)
    {
        throw std::exception();
    }
}

void ErrorReader::getError()
{
    if (!ec || !ec->valid())
    {
        std::cout << "ERROR: error buffer is invalid!" << std::endl;
        return NULL;
    }
    NMLTYPE type = ec->read();

    if (!type)
    {
        return NULL;
    }
    char error_buffer[LINELEN];

    
}
