#include <bits/stdc++.h>
#include <ext/numeric>
#include <ktl/util/extio.cpp>

using namespace std;
using __gnu_cxx::power;

uint64_t modinv(uint64_t x)
{
    return power(x, (1ull << 63) - 1);
}

struct dimatrix
{
    uint64_t a, b, c, d;
    uint64_t det() const { return a*d - b*c; }
    uint64_t tr() const { return a + d; }
    dimatrix inv() const
    {
        auto i = modinv(det());
        return {d*i, -b*i, -c*i, a*i};
    }
};

dimatrix operator* (const dimatrix& A, const dimatrix& B)
{
    return {
        A.a*B.a + A.b*B.c, A.a*B.b + A.b*B.d,
        A.c*B.a + A.d*B.c, A.c*B.b + A.d*B.d
    };
}

ostream& operator<< (ostream& out, const dimatrix& m)
{
    return out << "{" << m.a << ", " << m.b << ", " << m.c << ", " << m.d << "}";
}

struct __gen_hash
{
    dimatrix H[32];
    __gen_hash()
    {
        mt19937_64 gen(1337);
        for(size_t i = 0; i < 32; i++)
        {
            dimatrix M;
            do {
                M.a = gen(); M.b = gen(); M.c = gen(); M.d = gen();
            } while(M.det() % 2 == 0);
            H[i] = M;
        }
    }
    const dimatrix& operator[] (size_t i) const
    {
        return H[i];
    }
} mono;

struct trace_hash
{
    string s;
    vector<dimatrix> pref, prefinv;
    trace_hash(string _s) : s(_s)
    {
        size_t n = s.size();

        pref.resize(n+1, {1, 0, 0, 1});
        prefinv = pref;
        for(size_t i = 0; i < n; i++)
        {
            pref[i+1] = pref[i] * mono[size_t(s[i] - 'a')];
            prefinv[i+1] = pref[i+1].inv();
        }
    }

    uint64_t operator() (uint64_t L, uint64_t R)
    {
        return (prefinv[L] * pref[R]).tr();
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    string s;
    cin >> s;

    const size_t n = s.size();
    trace_hash H(s);


    size_t q;
    cin >> q;
    using query_t = pair<string, size_t>;
    vector<query_t> queries(q);
    for(size_t i = 0; i < q; i++)
        cin >> queries[i].first, queries[i].second = i;
    sort(queries.begin(), queries.end(), [&](const query_t& lhs, const query_t& rhs) {
        return lhs.first.size() < rhs.first.size();
    });


    vector<size_t> result(q);

    size_t mm = 0;
    unordered_map<uint64_t, size_t> hashes(n + 1);
    hashes.reserve(6*n);

    for(const auto& query : queries)
    {
        auto [x, t] = query;

        const size_t m = x.size();
        if(m != mm)
        {
            mm = m;
            for(size_t i = 0; i+m <= n; i++)
                hashes[H(i, i+m)]++;
        }

        trace_hash G(x);
        auto g = G(0, m);

        result[t] = hashes[g];
    }

    for(auto v : result)
        cout << v << '\n';


}
