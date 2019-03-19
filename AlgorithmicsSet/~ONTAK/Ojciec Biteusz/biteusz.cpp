#include <iostream>
#include <set>

using namespace std;

const size_t MAX = 1 << 19, MAX_T = 1 << 20;

template<typename T, T(*F)(T, T), T NONE>
struct segment_tree
{
    uint32_t N = 2*MAX;
    T values[2*MAX];
    segment_tree(uint32_t n = MAX - 1)
    {
        N = 1u << (33 - __builtin_clz(n));
        fill(values, values + N, NONE);
    }
    T& operator[] (uint32_t i) { return values[i + N/2]; }
    void build()
    {
        for(uint32_t i = N/2; i --> 0;)
            values[i] = F(values[2*i], values[2*i+1]);
    }
    void set(uint32_t i, T v)
    {
        i += N/2;
        values[i] = v;
        while(i > 1)
            i /= 2, values[i] = F(values[2*i], values[2*i+1]);
    }
    T get(uint32_t i, uint32_t t1, uint32_t t2, uint32_t s1, uint32_t s2)
    {
        if(s2 < t1 or t2 < s1)
            return NONE;
        else if(s1 <= t1 and t2 <= s2)
            return values[i];
        else
            return F(get(2*i+0, t1, (t1+t2)/2+0, s1, s2),
                     get(2*i+1, (t1+t2)/2+1, t2, s1, s2));
    }
    T get(uint32_t s1, uint32_t s2)
        { return get(1, 0, N/2-1, s1, s2); }
};

uint32_t min_u32(uint32_t a, uint32_t b) { return a<b ? a : b; }
uint32_t max_u32(uint32_t a, uint32_t b) { return a>b ? a : b; }

template<typename T>
T max(const set<T>& S) { return *(--S.end()); }
template<typename T>
T min(const set<T>& S) { return *S.begin(); }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, t;
    cin >> n >> t;
    static segment_tree<uint32_t, min_u32, -1u> min_tree(n), nxt_tree(n);
    static segment_tree<uint32_t, max_u32, 0> max_tree(n);
    static set<uint32_t> occ[MAX_T];
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a;
        cin >> a;
        min_tree[i] = max_tree[i] = a;
        if(not occ[a].empty())
            nxt_tree[max(occ[a])] = i;
        occ[a].insert(i);
    }
    min_tree.build(); max_tree.build(); nxt_tree.build();
    uint32_t q;
    cin >> q;
    while(q --> 0)
    {
        uint32_t k;
        cin >> k;
        if(k == 1)
        {
            uint32_t l, r;
            cin >> l >> r; l--; r--;
            if(max_tree.get(l, r) - min_tree.get(l, r) == r - l and
               nxt_tree.get(l, r) > r)
                cout << "YES\n";
            else
                cout << "NO\n";
        }
        else if(k == 2)
        {
            uint32_t p, v;
            cin >> p >> v; p--;
            uint32_t u = min_tree[p];
            if(u == v)
                continue;
            auto it = occ[u].find(p);
            if(it != occ[u].begin())
            {
                auto ita = it, itb = it; ita--; itb++;
                if(itb != occ[u].end())
                    nxt_tree.set(*ita, *itb);
                else
                    nxt_tree.set(*ita, -1u);
            }
            occ[u].erase(it);
            it = occ[v].insert(p).first;
            auto itb = it; itb++;
            if(itb != occ[v].end())
                nxt_tree.set(*it, *itb);
            else
                nxt_tree.set(*it, -1u);
            if(it != occ[v].begin())
            {
                auto ita = it; ita--;
                nxt_tree.set(*ita, *it);
            }
            min_tree.set(p, v); max_tree.set(p, v);
        }
    }
}
