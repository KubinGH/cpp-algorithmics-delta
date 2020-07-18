#include <bits/stdc++.h>
#include <ext/numeric>
#ifndef XHOVA
#include "gondola.h"
#endif

using namespace std;
using __gnu_cxx::power;

void normalize(int n, int A[])
{
    int k = -1;
    for(int i = 0; i < n and k == -1; i++)
        if(A[i] <= n)
            k = (n + i - (A[i]-1)) % n;
    if(k != -1)
        rotate(A, A + k, A + n);
}

int valid(int n, int A[])
{
    normalize(n, A);
    for(int i = 0; i < n; i++)
        if(A[i] <= n and A[i]-1 != i)
            return false;
    return unordered_set<int>(A, A + n).size() == (size_t)n;
}

int replacement(int n, int A[], int out[])
{
    normalize(n, A);
    vector<pair<int, int>> re;
    for(int i = 0; i < n; i++)
        if(A[i] > n)
            re.emplace_back(A[i], i);
    sort(re.begin(), re.end());

    vector<int> B(n);
    iota(B.begin(), B.end(), 1);
    int l = 0;
    for(auto [x, i] : re)
        while(n+l < x)
            out[l++] = B[i], B[i] = n+l;
    return l;
}

constexpr uint64_t Mod = 1e9 + 9;
struct mod_multiplies : multiplies<uint64_t>
{
    uint64_t operator() (uint64_t a, uint64_t b) { return (a * b) % Mod; }
} Z;

int countReplacement(int n, int A[])
{
    if(not valid(n, A))
        return 0;

    vector<int> re;
    for(int i = 0; i < n; i++)
        if(A[i] > n)
            re.push_back(A[i]);
    sort(re.begin(), re.end());

    uint64_t result = n == (int)re.size() ? n : 1;

    vector<int> B(n);
    iota(B.begin(), B.end(), 1);
    int l = 1;
    for(int k = 0; k < (int) re.size(); k++)
    {
        result *= power(uint64_t(re.size() - k), re[k] - (n+l), Z);
        result %= Mod;
        l = re[k] - n + 1;
    }

    return result;
}
