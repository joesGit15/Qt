#include "shared.h"

int main(int argc, char *argv[])
{
    Shared sh;

    sh.Call();

    int n = GetInt();

    printf("Getint = %d\n",n);

    return 0;
}
