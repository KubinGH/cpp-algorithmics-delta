#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

int main()
{
    uint32_t n;
    cin >> n;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a;
        cin >> a;
        cout << (char)(80-((a%2)<<1));
    }
}
