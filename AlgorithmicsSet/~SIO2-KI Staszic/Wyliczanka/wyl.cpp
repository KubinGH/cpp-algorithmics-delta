#include <bits/stdc++.h>

using namespace std;

struct egcd_res { int64_t d, x, y; };
egcd_res egcd(int64_t a, int64_t b)
{
    if(a == 0)
        return {b, 0, 1};
    auto r = egcd(b % a, a);
    return {r.d, r.y - (b/a)*r.x, r.x};
}

uint64_t umod(int64_t a, int64_t b) { int64_t x = a%b; return x < 0 ? x + b : x; }

pair<uint64_t, uint64_t> crt(vector<pair<uint64_t, uint64_t>> congo)
{
    while(congo.size() > 1)
    {
        uint64_t a1, n1, a2, n2;
        tie(a1, n1) = congo.back(); congo.pop_back();
        tie(a2, n2) = congo.back(); congo.pop_back();

        auto r = egcd(n1, n2);
        uint64_t d = r.d, m = n1 / d * n2;
        uint64_t m1 = umod(r.x, m), m2 = umod(r.y, m);
        if(umod(a1 - a2, d))
            return {0, 0};
        n1 /= d; n2 /= d;
        uint64_t b = (a1*m2%m*n2 + a2*m1%m*n1) % m;

        congo.emplace_back(b, m);
    }
    return congo.back();
}

int main()
{
    uint32_t n;
    cin >> n;

    vector<uint32_t> P(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> P[i];

    vector<uint32_t> A(n+1);
    A[0] = n-1;
    for(uint32_t i = 0; i < n; i++)
        A[P[i]] = i;

    vector<pair<uint64_t, uint64_t>> congo;

    deque<uint32_t> Q(n);
    iota(Q.begin(), Q.end(), 0);

    for(uint32_t i = 0; i < n; i++)
    {
        int64_t c = 0;
        while(Q.front() != A[i+1])
            c++, Q.push_back(Q.front()), Q.pop_front();
        Q.pop_front();
        uint64_t m = n - i, x = (m + c + 1) % m;
        congo.emplace_back(x, m);
    }

    auto r = crt(congo);

    if(r.second == 0)
        cout << "NIE\n";
    else
        cout << (not r.first ? r.second : r.first) << endl;
}
