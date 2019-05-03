#include <bits/stdc++.h>

using namespace std;

const size_t NAX = 1 << 24;

struct __DSIO_DECL { __DSIO_DECL() { ios_base::sync_with_stdio(false); cin.tie(nullptr); } } __DSIO;

int main()
{
    static array<uint64_t, NAX> F;
    static array<uint32_t, NAX> M;
    vector<uint32_t> P; P.reserve(1 << 21);

    size_t it = 0;
    F[1] = 1;
    for(uint32_t x = 2; x < NAX; x++)
    {
        if(not M[x])
        {
            M[x] = x;
            P.push_back(x);
            F[x] = 1 + (uint64_t) x * (x - 1);
        }
        for(size_t i = 0; i < P.size() and P[i] <= M[x] and P[i]*x < NAX; i++)
        {
            M[x * P[i]] = P[i];
            uint32_t y = x, z = P[i];
            while(y % P[i] == 0) y /= P[i], z *= P[i], it++;
            if(y == 1)
                F[z] = F[x] + (uint64_t) z * (z - z/P[i]);
            else
                F[y * z] = F[y] * F[z];
        }
    }
    cerr << 1. * clock() / CLOCKS_PER_SEC << " " << it << endl;

    size_t T;
    cin >> T;
    while(T --> 0)
    {
        size_t n;
        cin >> n;
        cout << F[n] << "\n";
    }
}