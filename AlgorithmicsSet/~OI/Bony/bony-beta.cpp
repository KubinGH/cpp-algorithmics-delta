#include <bits/stdc++.h>

using namespace std;

const size_t N = 1 << 20;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t m;
    cin >> m;
    static uint32_t B[N], U[N];
    vector<uint64_t> R;
    static bool E[N], S[N];
    for(uint32_t i = 0; i < m; i++)
        cin >> B[i], E[B[i]] = true;
    uint32_t n;
    cin >> n;
    uint64_t tk = 1;
    while(n --> 0)
    {
        uint32_t a;
        cin >> a;
        U[a] = max(a, U[a]);
        for(uint32_t x = U[a], t = 0, c = a; x <= B[m-1] and c --> 0; x += a, t++)
        {
            if(S[x])
                c++, t--;
            else
            {
                if(E[x])
                    R.push_back(tk + t), E[x] = false;
                S[x] = true;
            }
            U[a] = x + a;
        }
        tk += a;
    }
    cout << R.size() << '\n';
    for(uint64_t r : R)
        cout << r << '\n';
}
