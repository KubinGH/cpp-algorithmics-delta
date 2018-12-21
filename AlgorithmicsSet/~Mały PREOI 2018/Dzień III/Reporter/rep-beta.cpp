#include <bits/stdc++.h>

using namespace std;

template<typename T>
T lomul(T x, T m)
{
    T r = x;
    if(x % m)
        r += (m - x%m);
    return r;
}
template<typename T>
T himul(T x, T m)
{
    return x - x%m;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    vector<uint32_t> step(n+1);
    vector<uint32_t> group(n+1, 1);
    step[0] = 1;
    for(uint32_t i = 1; i <= n; i++)
    {
        uint32_t d; cin >> d;
        uint32_t s = lomul(d, step[i-1]);
        step[i] = s;
        if(step[i] == step[i-1])
        {
            if(group[i-1] == 1)
                group[i] = -1u;
            else
                group[i] = group[i-1] - 1;
            group[i + group[i]]++;
        }
    }

    for(uint32_t qi = 0; qi < q; qi++)
    {
        uint32_t t; int32_t L, R;
        cin >> t >> L >> R;
        uint32_t r = 0;
        for(uint32_t i = 0; i <= n; i += group[i])
        {
            int32_t gL = himul(t, step[i]) - (i + group[i] - 1),
                    gR = himul(t, step[i]) - i;
            int32_t iL = max(gL, L), iR = min(gR, R);
            if(iL <= iR)
                r += iR - iL + 1;
        }
        cout << r << "\n";
    }
}
