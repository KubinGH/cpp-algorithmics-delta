#include <bits/stdc++.h>

using namespace std;

const size_t MAX_N = 30, MAX_K = 12;

uint32_t popcount(uint32_t i)
{
    return __builtin_popcount(i);
}

void for_each_bit(uint32_t i, function<void(uint32_t)> F)
{
    for(uint32_t j = i, p = 0, b = j%2; j; p++, j /= 2, b = j % 2)
        if(b) F(p);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k, s;
    cin >> n >> k >> s;
    static array<uint32_t, MAX_N> A;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    sort(A.begin(), A.begin() + n);
    static array<uint32_t, 1u << (MAX_N/2 + 1)> X, Y;
    static array<set<uint32_t>, MAX_K+1> B;
    uint32_t b1 = (1u << ((n/2) + (n%2))), b2 = (1u << (n/2));
    for(uint32_t i = 0; i < b1; i++)
    {
        if(popcount(i) <= k)
            for_each_bit(i, [&](uint32_t p) { X[i] += A[2*p]; } );
        else
            X[i] = 1 << 30;
        //cout << X[i] << " ";
    }
    //cout << endl;
    for(uint32_t i = 0; i < b2; i++)
    {
        if(popcount(i) <= k)
        {
            for_each_bit(i, [&](uint32_t p) { Y[i] += A[2*p+1]; } );
            B[popcount(i)].insert(Y[i]);
        }
        else
            Y[i] = 1 << 30;
        //cout << Y[i] << " ";
    }
    //cout << endl;
    uint32_t result = 0;
    for(uint32_t i = 0; i < b1; i++)
    {
        if(popcount(i) > k or X[i] > s)
            continue;
        //cout << i << " (" << popcount(i) << ")" << " " << X[i] << endl;
        for(uint32_t b = 0; b <= k - popcount(i); b++)
        {
            if(B[b].empty() or X[i] + *B[b].begin() > s)
                continue;
            auto it = B[b].upper_bound(s - X[i]);
            if(it == B[b].begin())
                continue;
            it--;
            if(X[i] + *it <= s)
                result = max(result, X[i] + *it);
        }
    }
    cout << result;
}
