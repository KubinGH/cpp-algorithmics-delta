#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 19, MAX_K = 20;

typedef pair<uint32_t, uint32_t> pair_u32;

template<typename T, size_t K, T(*F)(T, T), T(*GET_NONE)()>
struct segment_tree
{
    static const size_t N = 1u << K;
    static constexpr T NONE = GET_NONE();
    size_t n, k;
    T values[N];
    segment_tree(size_t _k = K)
    {
        n = 1u << (k = _k+1);
        fill(begin(values), end(values), NONE); build();
    }
    void build()
    {
        for(uint32_t i = n/2; i --> 0; )
            values[i] = F(values[2*i], values[2*i+1]);
    }
    T get(size_t sbegin, size_t send)
    {
        T result = NONE;
        for(sbegin += n/2, send += n/2+1; sbegin < send; sbegin >>= 1, send >>= 1)
        {
            if(sbegin & 1) result = F(result, values[sbegin++]);
            if(send   & 1) result = F(result, values[--send]);
        }
        return result;
    }
};
pair_u32 merge_leaders(pair_u32 a, pair_u32 b)
{
    if(a.first == b.first)
        return {a.first, a.second + b.second};
    else if(a.second < b.second)
        return {b.first, b.second - a.second};
    else if(a.second > b.second)
        return {a.first, a.second - b.second};
    else
        return {0, 0};
}
constexpr pair_u32 get_none() { return {0, 0}; }

uint32_t log2floor(uint32_t x) { return 31 - __builtin_clz(x); }
uint32_t log2ceil (uint32_t x) { return log2floor(2*x-1); }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    static segment_tree<pair_u32, MAX_K, merge_leaders, get_none>
        tree(log2ceil(n));
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> tree.values[i+tree.n/2].first;
        tree.values[i+tree.n/2].second = 1;
    }
    tree.build();
    static pair_u32 queries[MAX];
    static vector<uint32_t> begin_points[MAX], end_points[MAX];
    static uint32_t proposal[MAX];
    for(uint32_t i = 0; i < q; i++)
    {
        uint32_t a, b;
        cin >> a >> b; a--; b--; queries[i] = {a, b};
        begin_points[a].push_back(i);
        end_points[b+1].push_back(i);
        proposal[i] = tree.get(a, b).first;
    }
    static uint32_t begin_count[MAX], end_count[MAX], curr_count[MAX];
    for(uint32_t i = 1; i <= n; i++)
    {
        curr_count[tree.values[i+tree.n/2-1].first]++;
        for(uint32_t p : begin_points[i])
            begin_count[p] = curr_count[proposal[p]];
        for(uint32_t p : end_points[i])
            end_count[p] = curr_count[proposal[p]];
    }
    for(uint32_t i = 0; i < q; i++)
    {
        if(proposal[i] and end_count[i] - begin_count[i] > (queries[i].second - queries[i].first + 1)/2)
            cout << proposal[i] << "\n";
        else
            cout << "0\n";
    }
}
