#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e5, MAX_A = 1 << 20, BITS = 20;
const uint32_t MOD = 1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    static uint32_t A[MAX], R[MAX];
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    static tuple<uint32_t, uint32_t, uint32_t> D[MAX];
    for(uint32_t i = 0; i < q; i++)
        cin >> get<0>(D[i]) >> get<1>(D[i]), get<2>(D[i]) = i;
    static bitset<MAX_A> Q;
    vector<uint32_t> S = {0};
    Q[0] = true;
    sort(D, D + q); uint32_t iq = 0;
    uint32_t m = 1;
    for(uint32_t i = 0; i < n; i++)
    {
        if(not Q[A[i]])
        {
            if(i == 0 or not Q[A[i] ^ A[i-1]]) for(uint32_t j = S.size(); j --> 0;)
            {
                S.push_back(S[j] ^ A[i]);
                Q[S[j] ^ A[i]] = true;
            }
        }
        else
            m *= 2;
        m %= MOD;
        while(iq < q and get<0>(D[iq]) <= i+1)
        {
            if(Q[get<1>(D[iq])])
                R[get<2>(D[iq])] = m;
            iq++;
        }
    }
    for(uint32_t i = 0; i < q; i++)
        cout << R[i] << "\n";
}
