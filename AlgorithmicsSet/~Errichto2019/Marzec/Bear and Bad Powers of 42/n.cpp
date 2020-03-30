#include <bits/stdc++.h>

using namespace std;

const int64_t oo = 1e18, nop = INT64_MAX-1;

using delta_mt = pair<int64_t, int64_t>;
struct delta_merge
{
    delta_mt operator() (const delta_mt& old, const delta_mt& neu) const
    {
        if(neu.first != nop)
            return neu;
        else
            return {old.first, old.second + neu.second};
    }
};
struct delta_mutate
{
    void operator() (size_t i, size_t nodeL, size_t nodeR,
                     vector<int64_t>& values, vector<delta_mt>& mutate) const
    {
        if(mutate[i] == delta_mt{nop, 0})
            return;
        if(nodeL < nodeR)
        {
            mutate[2*i  ] = delta_merge{}(mutate[2*i  ], mutate[i]);
            mutate[2*i+1] = delta_merge{}(mutate[2*i+1], mutate[i]);
        }
        if(mutate[i].first != nop)
            values[i] = mutate[i].first;
        values[i] += mutate[i].second;
        mutate[i] = {nop, 0};
    }
};
template<typename T>
struct max_f
{
    T operator() (const T& a, const T& b) const { return max(a, b); }
};
constexpr delta_mt identity_element(delta_mutate) { return {nop, 0}; }
constexpr int64_t identity_element(max_f<int64_t>) { return 0; }


struct segment_tree
{
    max_f<int64_t> F;
    delta_mutate M;
    delta_merge S;
    size_t w;
    vector<int64_t> values;
    vector<delta_mt> mutate;
    segment_tree(size_t n)
    {
        w = 1 << __lg(2*n-1);
        values.resize(2*w, identity_element(F));
        mutate.resize(2*w, identity_element(M));
    }
    void pull(size_t i, size_t nodeL, size_t nodeR)
    {
        M(i, nodeL, nodeR, values, mutate);
    }
    int64_t val(size_t i)
    {
        if(mutate[i].first != nop)
            return mutate[i].first + mutate[i].second;
        return values[i] + mutate[i].second;
    }
    int64_t get(size_t i, size_t nodeL, size_t nodeR, size_t getL, size_t getR)
    {
        if(nodeR < getL or nodeL > getR)
            return identity_element(F);
        else if(getL <= nodeL and nodeR <= getR)
            return val(i);
        else
        {
            pull(i, nodeL, nodeR);
            return F(get(2*i, nodeL, (nodeL+nodeR)/2, getL, getR),
                     get(2*i+1, (nodeL+nodeR)/2+1, nodeR, getL, getR));
        }
    }
    int64_t get(size_t getL, size_t getR) { return get(1, 0, w-1, getL, getR); }
    int64_t get() { return get(0, w-1); }
    void mut(size_t i, size_t nodeL, size_t nodeR, size_t getL, size_t getR, delta_mt value)
    {
        if(nodeR < getL or nodeL > getR)
            {}
        else if(getL <= nodeL and nodeR <= getR)
            mutate[i] = S(mutate[i], value);
        else
        {
            pull(i, nodeL, nodeR);
            mut(2*i, nodeL, (nodeL+nodeR)/2, getL, getR, value);
            mut(2*i+1, (nodeL+nodeR)/2+1, nodeR, getL, getR, value);
            values[i] = F(val(2*i), val(2*i+1));
        }
    }
    void mut(size_t getL, size_t getR, delta_mt value) { return mut(1, 0, w-1, getL, getR, value); }
};

constexpr size_t G = 12;
constexpr int64_t baddie[G] = {
    1, 42, 1764, 74088, 3111696, 130691232, 5489031744,
    230539333248, 9682651996416, 406671383849472, 17080198121677824, +oo
};

bool bad(int64_t x)
{
    return binary_search(baddie, baddie+G, x);
}

pair<size_t, int64_t> find_max(segment_tree& tree)
{
    size_t i = 1, nodeL = 0, nodeR = tree.w - 1;
    while(nodeL < nodeR)
    {
        tree.pull(i, nodeL, nodeR);
        auto mid = (nodeL+nodeR) / 2;
        if(tree.val(i) == tree.val(2*i))
            i = 2*i, nodeR = mid;
        else
            i = 2*i+1, nodeL = mid+1;
    }
    return {i - tree.w, tree.val(i)};
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    map<size_t, int64_t> breaks = {{0, 0}, {n+1, 0}};
    for(size_t i = 0; i < n; i++)
    {
        int64_t x;
        cin >> x;
        breaks[i+1] = x;
    }

    segment_tree delta_tree(n);
    vector<segment_tree> group_trees(G, segment_tree(n));

    for(size_t g = 0; g < G; g++)
        group_trees[g].mut(0, group_trees[g].w-1, {-oo, 0});

    auto get = [&](size_t i) {
        auto it = breaks.upper_bound(i);
        return it->second + delta_tree.get(it->first - 1, it->first - 1);
    };
    auto group_repair = [&](size_t i) {
        for(size_t g = 0; g < G; g++)
            group_trees[g].mut(i, i, {-oo, 0});
        auto x = get(i);
        auto h = upper_bound(baddie, baddie+G, x) - baddie;
        group_trees[h].mut(i, i, {x, 0});
    };
    auto make_break = [&](size_t a) {
        auto it = breaks.lower_bound(a);
        breaks[a] = it->second;
        if(a) group_repair(a-1);
    };
    for(size_t i = 0; i < n; i++)
        group_repair(i);

    int R = 0;
    while(q --> 0)
    {
        char type;
        cin >> type;

        if(type == '1')
        {
            size_t i;
            cin >> i; i--;
            cout << get(i) << '\n';
        }
        else if(type == '2')
        {
            size_t a, b; int x;
            cin >> a >> b >> x; a--; b--;

            make_break(a); make_break(b+1);
            auto it = next(breaks.find(a));
            while(it->first <= b)
                breaks.erase(it++);
            breaks[b+1] = x;
            delta_tree.mut(a, b, {0, 0});
            for(size_t g = 0; g < G; g++)
                group_trees[g].mut(a, b, {-oo, 0});
            group_repair(b);
        }
        else if(type == '3')
        {
            size_t a, b; int x;
            cin >> a >> b >> x; a--; b--;

            make_break(a); make_break(b+1);

            while(true)
            {
                bool any = false;
                delta_tree.mut(a, b, {nop, x});
                for(size_t g = 0; g < G; g++)
                    group_trees[g].mut(a, b, {nop, x});
                for(size_t g = 0; g < G; g++)
                {
                    auto& T = group_trees[g];
                    while(T.val(1) >= baddie[g])
                    {
                        auto [i, v] = find_max(T);
                        T.mut(i, i, {-oo, 0});
                        group_trees[g+1].mut(i, i, {v, 0});
                        if(v == baddie[g]) any = true;
                    }
                }
                R++;
                if(not any) break;
            }
        }
    }
}
