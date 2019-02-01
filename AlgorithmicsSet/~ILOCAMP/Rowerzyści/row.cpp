#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

const uint64_t M = 1e9 + 7;

struct mod_multiplies : multiplies<uint64_t>
{
    uint64_t operator() (uint64_t a, uint64_t b) const { return (a*b) % M; }
};

int main()
{
    uint32_t n;
    cin >> n;
    vector<uint64_t> A(n), B(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    for(uint32_t i = 0; i < n; i++)
        cin >> B[i];
    {
        vector<uint32_t> P(n);
        iota(P.begin(), P.end(), 0);
        uint64_t r = -1llu;
        do {
            uint64_t s = 0;
            for(uint32_t i = 0; i < n; i++)
                s += (A[i] * B[P[i]]) % M, s %= M;
            r = min(r, s);
        } while(next_permutation(P.begin(), P.end()));
        cout << r << endl;
    }
    {
        uint64_t r = 0;
        uint32_t m = n;
        map<uint64_t, uint32_t> X, Y;
        for(uint32_t i = 0; i < n; i++)
            X[A[i]]++, Y[A[i]]++;
        for(uint32_t z = 0; m > 0; z++)
        {
            cout << z << endl;
            uint64_t f = 0;
            vector<uint64_t> Xd, Yd;
            for(auto a : X)
            {
                uint64_t x = a.first, y = power(x, M - 2, mod_multiplies());
                if(X[x] < Y[y])
                    Xd.push_back(x), Y[y] -= X[x], f += X[x], X[x] = 0;
                else if(X[x] > Y[y])
                    Yd.push_back(y), X[x] -= Y[y], f += Y[y], Y[y] = 0;
                else
                    Xd.push_back(x), Yd.push_back(y), f += X[x], X[x] = Y[y] = 0;
            }
            for(uint64_t d : Xd)
                X.erase(d);
            for(uint64_t d : Yd)
                Y.erase(d);
            r += f * z; r %= M; m -= f;
        }
        cout << r;
    }
}
