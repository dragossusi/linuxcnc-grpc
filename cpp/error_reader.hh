#include "linuxcnc.pb.h"

using linuxcnc::status::SystemMessage;

class ErrorReader
{
private:
    uint64_t timeSinceEpochMillisec();

public:
    ErrorReader();
    bool readError(SystemMessage *message);
};