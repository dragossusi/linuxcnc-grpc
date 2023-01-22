#include <iostream>
#include <string>
#include <chrono>

#include "error_reader.hh"

#include <stat_msg.hh>
#include <cmd_msg.hh>
#include <emc_nml.hh>
#include <nml.hh>
#include <nml_oi.hh>
#include <config.h>

#include <cmd_msg.hh>

#include "linuxcnc.pb.h"

using linuxcnc::status::MessageType;
using linuxcnc::status::SystemMessage;

static NML *ec;

uint64_t ErrorReader::timeSinceEpochMillisec()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

ErrorReader::ErrorReader()
{
    ec = new NML(emcFormat, "emcError", "xemc", EMC2_DEFAULT_NMLFILE);

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

bool ErrorReader::readError(SystemMessage *message)
{
    if (!ec || !ec->valid())
    {
        std::cout << "ERROR: error buffer is invalid!" << std::endl;
        return false;
    }
    NMLTYPE type = ec->read();

    if (!type)
    {
        std::cout << "Type is invalid " << type << std::endl;
        return false;
    }

    // read message

    std::string error;
    MessageType messageType;

    switch (type)
    {
    case EMC_OPERATOR_ERROR_TYPE:
        messageType = MessageType::Operator_Error;
        error = std::string(((EMC_OPERATOR_ERROR *)ec->get_address())->error);
        break;

    case EMC_OPERATOR_TEXT_TYPE:
        messageType = MessageType::Operator_Text;
        error = std::string(((EMC_OPERATOR_TEXT *)ec->get_address())->text);
        break;
    case EMC_OPERATOR_DISPLAY_TYPE:
        messageType = MessageType::Operator_Display;
        error = std::string(((EMC_OPERATOR_DISPLAY *)ec->get_address())->display);
        break;
    case NML_ERROR_TYPE:
        messageType = MessageType::NML_Error;
        error = std::string(((NML_ERROR *)ec->get_address())->error);
        break;
    case NML_TEXT_TYPE:
        messageType = MessageType::NML_Text;
        error = std::string(((NML_TEXT *)ec->get_address())->text);
        break;
    case NML_DISPLAY_TYPE:
        messageType = MessageType::NML_Display;
        error = std::string(((NML_DISPLAY *)ec->get_address())->display);
        break;
    default:
        messageType = MessageType::NML_Display;
        error = std::string("Unrecognized error " + std::to_string(type));
        break;
    }

    message->set_allocated_message(&error);
    message->set_type(messageType);
    message->set_timestamp_millis(timeSinceEpochMillisec());

    return true;
}