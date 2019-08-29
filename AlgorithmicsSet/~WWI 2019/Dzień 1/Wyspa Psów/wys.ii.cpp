#include <bits/stdc++.h>
#include <ext/numeric>

// -*- ktl/util/fastio.cpp -*-

#include <cstdint>
#include <cstdio>
#include <type_traits>
#include <iostream>

#ifdef _WIN32
#define getchar_unlocked getchar
#define putchar_unlocked putchar
#define fputs_unlocked fputs
#endif

using std::is_integral; using std::is_unsigned; using std::is_signed;
using std::make_unsigned;
using std::enable_if;

struct unlocked_cin
{
    char _whitespace_skip()
    {
        char lchar;
        while(isspace(lchar = getchar_unlocked())) {}
        return lchar;
    }
    unlocked_cin& operator>> (char& x)
    {
        x = _whitespace_skip();
        return *this;
    }
    template<typename T>
    typename enable_if<is_integral<T>::value && is_unsigned<T>::value, unlocked_cin&>::type
    operator>> (T& x)
    {
        x = 0;
        char lchar = _whitespace_skip(); 
        do {
            x *= 10, x += lchar - '0';
        } while(isdigit(lchar = getchar_unlocked()));
        return *this;
    }
    template<typename T>
    typename enable_if<is_integral<T>::value && is_signed<T>::value, unlocked_cin&>::type
    operator>> (T& x)
    {
        bool s = false; 
        x = 0;
        char lchar = _whitespace_skip();
        if(lchar == '-')
            s = true;
        else
            x += lchar - '0';
        while(isdigit(lchar = getchar_unlocked()))
            x *= 10, x += lchar - '0';
        if(s) x = -x;
        return *this;
    }
} ucin;

struct unlocked_cout
{
    unlocked_cout& operator<< (const char* c)
    {
        fputs_unlocked(c, stdout);
        return *this;
    }
    unlocked_cout& operator<< (char x)
    {
        putchar_unlocked(x);
        return *this;
    }
    template<typename T>
    typename enable_if<is_integral<T>::value && is_unsigned<T>::value, unlocked_cout&>::type
    operator<< (T x)
    {
        static char buffer[64];
        size_t i = 0;
        if(not x)
            buffer[i++] = '0';
        while(x)
            buffer[i++] = (x % 10) + '0', x /= 10;
        for(; i --> 0; )
            putchar_unlocked(buffer[i]);
        return *this;
    }
    template<typename T>
    typename enable_if<is_integral<T>::value && is_signed<T>::value, unlocked_cout&>::type
    operator<< (T x)
    {
        if(x < 0)
            putchar_unlocked('-'), x = -x;
        return *this << static_cast<typename make_unsigned<T>::type>(x);
    }
} ucout;

// -$- ktl/util/fastio.cpp -$-


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
