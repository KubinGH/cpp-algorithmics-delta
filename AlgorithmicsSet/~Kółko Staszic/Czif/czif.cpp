#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 10000;

bool mixcomp(pair<uint32_t, uint32_t> a, pair<uint32_t, uint32_t> b)
{
    return a.first > b.first or (not (a.first < b.first) and a.second < b.second);
}

int main()
{
    uint32_t z, p, t;
    cin >> z >> p >> t;
    static array<pair<uint32_t, uint32_t>, MAX> A;
    for(uint32_t i = 0; i < p; i++)
        A[i].second = i+1;
    for(uint32_t ti = 0; ti < t; ti++)
    {
        uint64_t c; uint32_t i, cp;
        cin >> c >> i >> cp;
        bitset<64> b(c);
        if(!b[z-i-1])
            A[cp-1].first++;
    }
    sort(A.begin(), A.begin() + p, mixcomp);
    for(uint32_t i = 0; i < 10 and i < p; i++)
        cout << A[i].second << " ";
}
