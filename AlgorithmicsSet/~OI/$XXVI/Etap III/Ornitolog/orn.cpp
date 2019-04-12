#include <bits/stdc++.h>

using namespace std;

uint32_t n, m, a, b, k;
uint32_t get()
{
    vector<uint32_t> D;
    D.reserve(k);
    uint32_t i = 0, j = -1u, c = a;
    while(k)
    {
        j = (n+m + i + c - 1) % (n + m);
        if(k == 1)
            break;
        else if(j < n)
            i = j, n--, k--, c = a;
        else
            i = j, m--, k--, c = b;
        D.push_back(j);
    }
    uint32_t r = j;
    for(uint32_t x = D.size(); x --> 0; )
        if(r >= D[x])
            r++;
    return r;
}

int main()
{
    cin >> n >> m >> a >> b >> k;
    cout << get() + 1;
}