#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<uint64_t> A(n);
    for(auto& a : A) cin >> a;

    const uint64_t x = *max_element(A.begin(), A.end());
    const size_t m = x >> max((int)__lg(x)/2 - 1, 0);

    vector<uint64_t> T;
    T.reserve(m);

    vector<bool> is_prime(m+1, true);
    for(size_t i = 2; i <= m; i++)
    {
        if(is_prime[i])
        {
            T.push_back((uint64_t)i * i);
            if(i < (1u << 16)) for(size_t j = i*i; j <= m; j += i)
                is_prime[j] = false;
        }
    }

    for(auto& a : A)
        cout << (binary_search(T.begin(), T.end(), a) ? "YES" : "NO") << '\n';
}
