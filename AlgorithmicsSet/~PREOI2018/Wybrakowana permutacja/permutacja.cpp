#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500000;
const size_t TSIZE = 1 << 20;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> A, P;
    static array<uint32_t, MAX+1> C, U;
    static array<bool, MAX+1> B;
    fill(B.begin() + 1, B.begin() + n + 1, true);
    vector<uint32_t> V;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        C[i+1] = C[i] + (A[i] == 0);
        if(A[i] != 0)
            V.push_back(i), B[A[i]] = false;
    }
    for(uint32_t i = 1; i < n+1; i++)
        U[i] = U[i-1] + B[i];
    uint32_t m = C[n];
    for(uint32_t vi = 0; vi < V.size(); vi++)
    {
        uint32_t i = V[vi];
        uint32_t p = 0;
        uint32_t v = 0;
        for(uint32_t vj = 0; vj < vi; vj++)
        {
            uint32_t j = V[vj];
            if(A[j] < A[i])
            {
                v = P[j] + min(U[A[i]] - U[A[j]], C[i] - C[j]);
                if(v > p)
                    p = v;
            }
        }
        p = max(p, min(U[A[i]], C[i]));
        p++;
        P[i] = p;
        v = P[i] + min(U[n] - U[A[i]], C[n] - C[i]);
        if(v > m)
            m = v;
    }
    cout << m;

}
