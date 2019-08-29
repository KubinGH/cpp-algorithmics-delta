#include "z2.h"
#include <cstdio>
#include <unistd.h>
#include <sstream>

int main()
{
    int stdout_save;
    static char buffer[4096];
    fflush(stdout);
    stdout_save = dup(STDOUT_FILENO);
    freopen("NUL", "a", stdout);
    setvbuf(stdout, buffer, _IOFBF, 1024);
    fun();
    freopen("NUL", "a", stdout);
    dup2(stdout_save, STDOUT_FILENO);
    setvbuf(stdout, NULL, _IONBF, 1024);

    std::stringstream st;
    st << buffer;

    std::string _;
    unsigned long long secret;
    st >> _ >> secret;

    printf("%llu\n", secret);
}
