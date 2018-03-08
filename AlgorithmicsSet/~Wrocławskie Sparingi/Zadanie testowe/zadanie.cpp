#include <stdio.h>
using namespace std;
int main()
{
    char c; int n = 0;
    while((c = getchar()) and 48 <= c and c <= 57)
        n *= 10, n += c - 48;
    for(; n --> 0;) putchar(42);
}
