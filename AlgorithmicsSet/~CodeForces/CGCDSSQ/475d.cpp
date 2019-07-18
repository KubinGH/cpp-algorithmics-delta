#include <bits/stdc++.h>
#include <ktl/structures/sparse_table.cpp>
#include <ktl/general/binary_search.cpp>

using namespace std;

using uint = unsigned;

struct gcd_op { uint operator() (uint a, uint b) { return __gcd(a, b); }};
using gcd_table = sparse_table<uint, gcd_op>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    size_t n;
    cin >> n;

    vector<uint> A(n);
    for(size_t i = 0; i < n; i++)
        cin >> A[i];
    gcd_table T(A.begin(), A.end());

    map<uint, uint64_t> counter;

    for(size_t start = 0; start < n; start++)
    {
        vector<pair<uint, size_t>> run;
        run.emplace_back(A[start], start);
        while(run.back().second + 1 < n and run.back().first > 1)
        {
            uint prev; size_t frag;
            tie(prev, frag) = run.back();
            size_t frag_stop = first_true(frag+1, n, [&] (size_t i) {
                return T(start, i) < prev;
            });
            run.emplace_back(T(start, frag_stop), frag_stop - 1);
        }
        size_t i = start;
        uint c = 0;
        for(auto p : run)
        {
            counter[c] += p.second - i;
            c = p.first; i = p.second;
        }
        counter[c] += n - i;
    }

    size_t q;
    cin >> q;
    while(q --> 0)
    {
        uint x;
        cin >> x;
        cout << counter[x] << '\n';
    }
}
