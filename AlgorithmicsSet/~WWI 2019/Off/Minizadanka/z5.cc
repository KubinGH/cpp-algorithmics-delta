#include <cstdio>

void fun(long long x) {
    auto sekret = 133705ull;
    
    if (x*2 < x*3 && x*3 > x*4)
        printf("%llu\n", sekret);
}
