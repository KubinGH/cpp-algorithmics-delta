#include <bits/stdc++.h>

using namespace std;

vector<uint64_t> A;

unordered_map<uint64_t, bool> cache;
bool win(uint64_t n)
{
    if(n == 0)
        return false;
    if(cache.count(n))
        return cache[n];
    for(auto a : A)
        if(not win(n / a))
            return cache[n] = true;
    return cache[n] = false;
}


int main()
{
    uint64_t n; size_t k;
    cin >> n >> k;
    A.resize(k);
    for(size_t i = 0; i < k; i++)
        cin >> A[i];
    cout << (win(n) ? "MONAD" : "MONOID VAN DER ENDOFUNKTOR");
}
