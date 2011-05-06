#ifndef TEMPLATES_H_INCLUDED
#define TEMPLATES_H_INCLUDED

#include "Log.h"

template<class T>
Log& operator<<(Log& log, T& data)
{
    log.ref_buff() << data;
    return log;
}

#endif // TEMPLATES_H_INCLUDED
