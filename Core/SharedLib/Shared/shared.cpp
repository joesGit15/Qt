#include "shared.h"


Shared::Shared()
{
}

void Shared::Call()
{
    printf("Call Ok\n");
}

int GetInt()
{
    printf("Call Int Ok\n");
    return 0;
}
