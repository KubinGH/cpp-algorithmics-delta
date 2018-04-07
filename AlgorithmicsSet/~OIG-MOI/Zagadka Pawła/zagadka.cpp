#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 2e5;

uint64_t gcd(uint64_t a, uint64_t b)
{
    return __gcd(a, b);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t n, k;
    cin >> n >> k;
    vector<uint64_t> k_divisors;
    for(uint64_t i = 1; i <= floor(sqrt(k)); i++)
    {
        if(k % i == 0)
        {
            k_divisors.push_back(i);
            if(k != i * i)
                k_divisors.push_back(k / i);
        }
    }
    sort(k_divisors.begin(), k_divisors.end());
    static array<uint64_t, MAX> A;
    set<uint64_t> S;
    unordered_map<uint64_t, uint64_t> M, C;
    for(uint64_t i = 0; i < n; i++)
    {
        cin >> A[i];
        A[i] %= k; if(A[i] == 0) A[i] = k;
        M[A[i]]++;
        S.insert(A[i]);
    }
    for(uint64_t a : S)
    {
        for(uint64_t d : k_divisors)
        {
            if(a % d == 0)
                C[d] += M[a];
        }
    }
    uint64_t result = 0;
    for(uint64_t a : S)
    {
        for(uint64_t d : k_divisors)
        {
            if(a % d == 0)
                C[d] -= M[a];
        }
        result += M[a] * C[k / gcd(a, k)];
        if((a * a) % k == 0)
            result += M[a] * (M[a] - 1) / 2;
    }
    cout << n*(n-1)/2 - result << endl;
}
