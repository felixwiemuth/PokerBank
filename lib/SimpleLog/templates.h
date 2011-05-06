#ifndef TEMPLATES_H_INCLUDED
#define TEMPLATES_H_INCLUDED

#include "Log.h"

template<class T>
std::ostream& operator<<(Log& log, T& data) //TODO does not work in all cases like stringstreams... e.g. "log << /*double val*/ * 100 << "text";" would not work
{
    log.ref_buff() << data;
    return log.ref_buff();
}

#endif // TEMPLATES_H_INCLUDED
