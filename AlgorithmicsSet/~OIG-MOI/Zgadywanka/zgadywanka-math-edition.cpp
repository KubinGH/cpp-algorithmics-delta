#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

int main()
{
    string W;
    cin >> W;
    uint32_t m = 0;
    for(uint32_t i = 0; i < W.size(); i++)
    {
        if(W[i] != '?')
            m += W[i] - '0';
        m %= 9;
    }
    cout << 9 - m;
}
