#include <bits/stdc++.h>

using namespace std;

const size_t N = 1 << 20;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    vector<uint32_t> P(N, true);
    P[0] = P[1] = false;
    for(uint32_t i = 2; i < N; i += 2)
    {
        if(P[i] and i < (1<<15)) for(uint32_t x = i*i; x < N; x += i)
            P[x] = false;
        if(i == 2) i--;
    }
    for(uint32_t i = 1; i < N; i++)
        P[i] = P[i-1] + P[i];
    uint32_t n;
    cin >> n;
    while(n --> 0)
    {
        uint32_t a, b;
        cin >> a >> b;
        cout << P[b] - P[a-1] << "\n";
    }
}
