#ifndef SHARED_H
#define SHARED_H

#include "shared_global.h"

int SHAREDSHARED_EXPORT GetInt();

class SHAREDSHARED_EXPORT Shared
{

public:
    Shared();
    void Call();
};

#endif // SHARED_H
