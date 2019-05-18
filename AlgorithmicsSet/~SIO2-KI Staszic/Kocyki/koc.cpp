#include <bits/stdc++.h>

using namespace std;

template<typename T>
using _vector = array<T, (1 << 22)>;

template<typename T, typename ChildrenOp,
         typename MT, typename MutateOp, typename MergeOp>
struct segment_tree_i
{
    ChildrenOp F;
    MutateOp M;
    MergeOp S;
    size_t w;
    _vector<T> values;
    _vector<MT> mutate;
    segment_tree_i(size_t n, ChildrenOp f = {}, MutateOp m = {}, MergeOp s = {})
        : F(f), M(m), S(s)
    {
        w = 1 << __lg(2*n-1);
        //values.resize(2*w, identity_element(F));
        //mutate.resize(2*w, identity_element(M));
        fill(values.begin(), values.end(), identity_element(F));
        fill(mutate.begin(), mutate.end(), identity_element(M));
    }
    void pull(size_t i, size_t nodeL, size_t nodeR)
    {
        M(i, nodeL, nodeR, values, mutate);
    }
    T get(size_t i, size_t nodeL, size_t nodeR, size_t getL, size_t getR)
    {
        pull(i, nodeL, nodeR);
        if(nodeR < getL or nodeL > getR)
            return identity_element(F);
        else if(getL <= nodeL and nodeR <= getR)
            return values[i];
        else
        {
            return F(get(2*i, nodeL, (nodeL+nodeR)/2, getL, getR),
                     get(2*i+1, (nodeL+nodeR)/2+1, nodeR, getL, getR));
        }
    }
    T get(size_t getL, size_t getR) { return get(1, 0, w-1, getL, getR); }
    void mut(size_t i, size_t nodeL, size_t nodeR, size_t getL, size_t getR, MT value)
    {
        pull(i, nodeL, nodeR);
        if(nodeR < getL or nodeL > getR)
            {}
        else if(getL <= nodeL and nodeR <= getR)
        {
            mutate[i] = S(mutate[i], value);
            pull(i, nodeL, nodeR);
        }
        else
        {
            mut(2*i, nodeL, (nodeL+nodeR)/2, getL, getR, value);
            mut(2*i+1, (nodeL+nodeR)/2+1, nodeR, getL, getR, value);
            values[i] = F(values[2*i], values[2*i+1]);
        }
    }
    void mut(size_t getL, size_t getR, MT value) { return mut(1, 0, w-1, getL, getR, value); }
};

struct pair_i64 { int64_t first, second; };

struct pairwise_sum_i64
{
    pair_i64 operator() (const pair_i64& a, const pair_i64& b)
    {
        return {a.first+b.first, a.second+b.second};
    }
};

pair_i64 identity_element(pairwise_sum_i64) { return {0, 0}; }

struct pull_q_add
{
    void operator() (size_t i, size_t nodeL, size_t nodeR,
                     _vector<pair_i64>& values, _vector<int64_t>& mutate)
    {
        const int64_t x = mutate[i], len = nodeR - nodeL + 1;
        values[i].second += values[i].first * 2*x + len * x*x;
        values[i].first += len * x;
        if(nodeL < nodeR)
        {
            mutate[2*i] += x;
            mutate[2*i+1] += x;
        }
        mutate[i] = 0;
    }
};

int64_t identity_element(pull_q_add) { return 0; }

using q_segment_tree = segment_tree_i<
    pair_i64, pairwise_sum_i64,
    int64_t, pull_q_add, plus<int64_t>
>;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    size_t n, a, b;
    cin >> n >> a >> b;

    vector<pair<size_t, size_t>> pos(n);
    size_t xax = 0, yax = 0;
    for(size_t i = 0; i < n; i++)
    {
        cin >> pos[i].first >> pos[i].second;
        xax = max(xax, pos[i].first);
        yax = max(yax, pos[i].second);
    }

    sort(pos.begin(), pos.end());

    static q_segment_tree T(yax + b);
    uint64_t result_n = 0, result_m = 0,
             last_query_n = 0, last_query_m = 0;
    const uint64_t split = (uint64_t) n * (n - 1);
    bool change = false;

    for(size_t x = 0, u = 0, w = 0; x <= xax + a; x++)
    {
        change = false;
        while(u < n and pos[u].first <= x)
        {
            T.mut(pos[u].second, pos[u].second + b - 1, 1);
            u++;
            change = true;
        }
        while(w < n and pos[w].first + a <= x)
        {
            T.mut(pos[w].second, pos[w].second + b - 1, -1);
            w++;
            change = true;
        }
        if(change)
        {
            auto p = T.get(0, T.w - 1);
            uint64_t o = p.second - p.first;
            last_query_n = o / split;
            last_query_m = o % split;
        }
        result_n += last_query_n;
        result_m += last_query_m;
    }
    result_n += result_m / split;
    result_m %= split;

    double result = result_n + (double)result_m / split;
    cout << fixed << setprecision(8) << result << endl;
}
