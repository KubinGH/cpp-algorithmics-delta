#include <bits/stdc++.h>

using namespace std;

template<typename T>
T lcm(T a, T b) { return a*b / __gcd(a, b); }

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<uint64_t> A(n);
    for(auto& a : A)
        cin >> a;

    vector<uint64_t> L(1 << n);
    L[0] = 1;
    for(size_t x = 1; x < (1u << n); x++)
        L[x] = lcm(L[x & (x - 1)], A[__lg(x & -x)]);

    while(m --> 0)
    {
        uint64_t q;
        cin >> q;

        uint64_t lo = 1, hi = (uint64_t)1 << 62;
        while(lo < hi)
        {
            uint64_t mid = (lo + hi) / 2;
            uint64_t k = 0;
            for(size_t x = 1; x < (1u << n); x++)
            {
                uint64_t c = mid / L[x];
                if(__builtin_popcount(x) % 2)
                    k += c;
                else
                    k -= c;
            }
            if(k >= q)
                hi = mid;
            else
                lo = mid+1;
        }
        cout << lo << endl;
    }
}
