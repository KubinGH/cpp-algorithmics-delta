#include <stdlib.h>
#include <cstdio>

typedef unsigned long long(*theptr)();

unsigned long long fun()
{
    theptr ptr = (theptr)((void*)&fun + 63);
    return ptr();
}

int main()
{
    printf("%llu", fun());
}
