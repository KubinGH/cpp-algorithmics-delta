#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 18;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, w;
    cin >> n >> w;
    static array<uint32_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    static array<uint32_t, 1u << MAX> S;
    for(uint32_t i = 0; i < (1u << n); i++)
    {
        for(uint32_t k = i, b = k % 2, j = 0; k > 0; k >>= 1, b = k % 2, j++)
            S[i] += A[j] * b;
    }
    static array<uint32_t, 1u << MAX> R;
    static array<vector<vector<uint32_t>>, 1u << MAX> V;
    R.fill(1 << 29);
    R[0] = 0;
    uint32_t f = (1u << n);
    for(uint32_t i = 1; i < f; i++)
    {
        if(S[i] <= w)
        {
            R[i] = 1;
            V[i].push_back(vector<uint32_t>());
            for(uint32_t k = i, b = k % 2, j = 0; k > 0; k >>= 1, b = k % 2, j++)
                if(b == 1)
                    V[i].back().push_back(j);
            continue;
        }
        uint32_t pop = __builtin_popcount(i);
        R[i] = pop;
        uint32_t ua = 0, ub = i;
        for(uint32_t a = 1; a < (1u << (31 - __builtin_clz(i))); a++)
        {
            uint32_t b = i ^ a;
            if(R[a] + R[b] < R[i] and ((a ^ b) == i))
            {
                ua = a; ub = b;
                R[i] = R[a] + R[b];
            }
        }
        if(R[i] == pop)
        {
            for(uint32_t k = i, b = k % 2, j = 0; k > 0; k >>= 1, b = k % 2, j++)
            {
                if(b == 1)
                {
                    V[i].push_back(vector<uint32_t>());
                    V[i].back().push_back(j);
                }
            }
        }
        else
        {
            V[i].reserve(R[i]);
            V[i].insert(V[i].end(), V[ua].begin(), V[ua].end());
            V[i].insert(V[i].end(), V[ub].begin(), V[ub].end());
        }
    }
    cout << R[f-1] << '\n';
    for(uint32_t i = 0; i < V[f-1].size(); i++)
    {
        cout << V[f-1][i].size() << " ";
        for(uint32_t x : V[f-1][i])
            cout << x+1 << " ";
        cout << "\n";
    }
}
