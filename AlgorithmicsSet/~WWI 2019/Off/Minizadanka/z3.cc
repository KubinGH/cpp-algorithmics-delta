#include <cstdio>
void fun() {
    auto sekret = 133703ull;
    char buffer[20];

    sprintf(buffer, "%d");

    if (*(short*)buffer == '0') {
        printf("%llu\n", sekret);
    }
}
