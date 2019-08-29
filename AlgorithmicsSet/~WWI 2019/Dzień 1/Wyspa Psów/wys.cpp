#include <bits/stdc++.h>
#include <ext/numeric>
#include <ktl/util/fastio.cpp>

using namespace std;
using __gnu_cxx::power;

const size_t NAX = 1 << 18;

void pchain_ip (vector<size_t>& P, const vector<size_t>& Q)
{
    if(P.empty()) { P = Q; return; };
    if(Q.empty()) return;
    static size_t B[NAX];
    const size_t n = P.size();
    for(size_t i = 0; i < n; i++)
        B[i] = P[Q[i]];
    copy(B, B + n, P.begin());
}

struct pchain
{
    vector<size_t> operator() (const vector<size_t>& P, const vector<size_t>& Q)
    {
        vector<size_t> R = P;
        pchain_ip(R, Q);
        return R;
    }

    vector<size_t> operator[] (const vector<size_t>& P)
    {
        vector<size_t> Q(P.size());
        for(size_t i = 0; i < P.size(); i++)
            Q[P[i]] = i;
        return Q;
    }
};

vector<size_t> identity_element(pchain) { return {}; }

int main()
{
    size_t n, m, q;
    ucin >> n >> m >> q;

    vector<size_t> P(m);
    P.reserve(n);
    for(size_t i = 0; i < m; i++)
    {
        ucin >> P[i];
        if(P[i] == 1)
            P[i] = n + 1;
        P[i] -= 2;
    }

    for(size_t i = m; i < n; i++)
        P.push_back(i - 1);

    vector<vector<size_t>> P_pow;
    P_pow.push_back(P);
    for(size_t i = 1; (1u << i) <= n; i++)
        P_pow.push_back(power(P_pow.back(), 2, pchain{}));
    vector<vector<size_t>> P_part;
    P_part.emplace_back();
    P_part.push_back(P);
    for(size_t i = 2; i < 64; i++)
    {
        P_part.push_back(P_part.back());
        pchain_ip(P_part[i], P);
    }

    vector<pair<size_t, size_t>> queries(q);
    for(size_t i = 0; i < q; i++)
    {
        size_t r;
        ucin >> r;
        queries[i] = {n - r, i};
    }

    vector<size_t> order(n), Q(n);
    iota(Q.begin(), Q.end(), 0);

    size_t c = 0;

    auto jump_to = [&](size_t d) {
        for(size_t k = P_pow.size(); k --> 0; )
        {
            if(c < d and d - c < 64)
            {
                pchain_ip(Q, P_part[d - c]);
                c += d - c;
            }
            if(c + (1u << k) <= d)
                pchain_ip(Q, P_pow[k]), c += (1u << k);
        }
    };

    sort(queries.begin(), queries.end());

    for(auto query : queries)
    {
        if(not (query.first + 1 <= n - m + 1))
            break;
        jump_to(query.first + 1);
        auto it = find(Q.begin(), Q.end(), Q.size() - 1);
        order[c - 1] = it - Q.begin();
    }

    jump_to(n - m + 1);
    auto I = pchain{}[Q];
    for(size_t i = 0; i < m - 1; i++)
        order[n - m + 1 + i] = I[i];

    vector<size_t> answer(q);
    for(size_t i = 0; i < q; i++)
        answer[queries[i].second] = order[queries[i].first] + 1;

    for(auto x : answer)
        ucout << x << '\n';
}
