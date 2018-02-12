#include <bits/stdc++.h>

using namespace std;

typedef unsigned short int uint16_t;

int main()
{
    uint16_t n = 0;
    char c;
    while('0' <= (c = getchar()) and c <= '9')
    {
        n += c - '0';
    }
    cout << (n % 3 ? "NIE" : "TAK");
}
