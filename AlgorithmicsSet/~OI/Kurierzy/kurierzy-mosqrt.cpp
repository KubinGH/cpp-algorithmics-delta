#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

typedef tuple<uint32_t, uint32_t, uint32_t> tri_u32;

const size_t MAX = 5e4;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    uint32_t Q = floor(sqrt(n));
    auto mo_cmp = [Q](const tri_u32& lhs, const tri_u32& rhs) {
        if(get<0>(lhs) / Q != get<0>(rhs) / Q)
            return get<0>(lhs) < get<0>(rhs);
        else
            return get<1>(lhs) < get<1>(rhs);
    };
    static uint32_t A[MAX];
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i], A[i]--;
    static tri_u32 queries[MAX];
    for(uint32_t i = 0; i < q; i++)
    {
        uint32_t a, b;
        cin >> a >> b; a--; b--;
        queries[i] = tri_u32{a, b, i};
    }
    sort(queries, queries + q, mo_cmp);
    static uint32_t result[MAX], occ[MAX];
    set<pair<uint32_t, uint32_t>> occs;
    for(uint32_t i = 0; i < n; i++)
        occs.emplace(0, i);
    uint32_t x = 0, y = 0;
    auto add = [&](uint32_t i) {
        occs.erase({occ[A[i]], A[i]});
        occ[A[i]]++;
        occs.insert({occ[A[i]], A[i]});
    };
    auto remove = [&](uint32_t i) {
        occs.erase({occ[A[i]], A[i]});
        occ[A[i]]--;
        occs.insert({occ[A[i]], A[i]});
    };
    add(0);
    for(uint32_t qi = 0; qi < q; qi++)
    {
        uint32_t a, b, i; tie(a, b, i) = queries[qi];
        while(x > a) add(--x);
        while(y < b) add(++y);
        while(x < a) remove(x++);
        while(y > b) remove(y--);
        auto it = --occs.end();
        if(it->first > (y - x + 1) / 2)
            result[i] = it->second;
        else
            result[i] = -1u;
    }
    for(uint32_t i = 0; i < q; i++)
        cout << result[i]+1 << "\n";
}
