#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;
const uint64_t LIM = 1000000009;

uint64_t gcd(uint64_t a, uint64_t b)
{
    if(a == 0 or b == 0)
        return a ^ b;
    return __gcd(a, b);
}

uint64_t lcm(vector<uint64_t>& A)
{
    if(A.size() == 1)
        return A[0];
    uint32_t r = 1;
    for(uint32_t i = 0; i < A.size(); i++)
    {
        if(A[i] != 1) for(uint32_t j = i + 1; j < A.size(); j++)
            A[j] /= gcd(A[i], A[j]);
        r = (r * A[i]) % LIM;
    }
    return r;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> P;
    for(uint32_t i = 0; i < n; i++)
        cin >> P[i], P[i]--;
    vector<uint64_t> cycles;
    static array<bool, MAX> D;
    for(uint32_t c = 0; c < n; c++)
    {
        if(D[c]) continue;
        uint64_t v = 1;
        D[c] = true;
        while(not D[P[c]])
        {
            c = P[c];
            D[c] = true;
            v++;
        }
        cycles.push_back(v);
    }
    cout << lcm(cycles);

}
