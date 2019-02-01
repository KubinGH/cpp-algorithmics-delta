#include <bits/stdc++.h>

using namespace std;

uint32_t ceildiv(uint32_t a, uint32_t b) { return (a + b - 1) / b; }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t d[2], q;
    cin >> d[0] >> d[1] >> q;

    vector<uint32_t> r[2];
    for(uint32_t s = 0; s < 2; s++)
      for(uint32_t i = 0; i < d[s]; i++)
        if(r[s].empty() or ceildiv(d[s], r[s].back()+1) != ceildiv(d[s], i+1))
            r[s].push_back(i);

    vector<uint64_t> R(d[0]+d[1]-1, -1LLU);
    for(uint32_t i : r[0])
        for(uint32_t j : r[1])
            R[i+j] = min(R[i+j], uint64_t(ceildiv(d[0], i+1)) * uint64_t(ceildiv(d[1], j+1)));

    for(uint32_t i = 1; i < d[0]+d[1]-1; i++)
        R[i] = min(R[i-1], R[i]);

    for(uint32_t i = 0; i < q; i++)
    {
        uint32_t k;
        cin >> k;
        cout << R[k] << "\n";
    }
}
