#include "z3.h"

extern "C" int sprintf(char* buf, const char* _) { buf[1] = 0; buf[0] = '0'; }

int main()
{
    fun();
}
