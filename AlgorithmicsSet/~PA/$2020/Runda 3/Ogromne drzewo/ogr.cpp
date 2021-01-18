#include <bits/stdc++.h>

using namespace std;

const uint mod = 2e9 + 14;

uint Z(uint a, uint b) { return (uint64_t)a * b % mod;}
size_t n;
vector<uint> X;

vector<pair<uint, uint64_t>> dists(size_t a, size_t b, size_t c)
{
    uint d = a + b - 2*c;

    vector<uint64_t> T(n);
    vector<pair<uint, uint64_t>> P = {{d, Z(d, d + 1)}};

    for(size_t i = c+1; i < b; i++)
        T[i] += X[i] - 1;
    for(size_t i = c+1; i < a; i++)
        T[i] += X[i] - 1;

    if(a != c)
        T[a] += X[a];
    if(b != c)
        T[b] += X[b];
    T[c] += X[c] - (a!=c) - (b!=c);

    for(size_t i = c; i --> 0; )
    {
        // put 1 at d + 2(c - i)
        // put A[i] - (c!=0) level i at d + 2(c - i) + 2
    }

    return P;
}

vector<pair<uint, uint64_t>> dists(size_t a) { return dists(a, a, a); }

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t q;
    cin >> n >> q;

    X.resize(n);
    for(size_t i = 0; i < n - 1; i++)
        cin >> X[i];

    while(q --> 0)
    {
        size_t a, b, c;
        cin >> a >> b >> c;
        a--; b--; c--;


    }
}
