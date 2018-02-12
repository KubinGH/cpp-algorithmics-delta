#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> W, M;
    for(uint32_t i = 0; i < n; i++)
        cin >> W[i];
    for(uint32_t i = 0; i < n; i++)
        cin >> M[i];
    uint32_t wi = n - 1, r = 0;
    while(wi < n)
    {
        for(uint32_t i = 0; i < n and wi < n; i++)
        {
            if(W[wi] == M[i])
                wi--;
            if(i == 0 and wi < n)
                r++;
        }
    }
    cout << r;
}
