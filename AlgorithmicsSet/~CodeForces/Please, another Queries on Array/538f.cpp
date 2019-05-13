#include <bits/stdc++.h>
#include <ext/numeric>
#include <ext/functional>

using namespace std;
using __gnu_cxx::power;
using __gnu_cxx::identity_element;

const uint64_t MOD = 1e9 + 7;
const size_t MAX_A = 300;

template<typename T, typename ChildrenOp,
         typename MT, typename MutateOp, typename MergeOp>
struct segment_tree_i
{
    ChildrenOp F;
    MutateOp M;
    MergeOp S;
    size_t w;
    vector<T> values;
    vector<MT> mutate;
    segment_tree_i(size_t n, ChildrenOp f = {}, MutateOp m = {}, MergeOp s = {})
        : F(f), M(m), S(s)
    {
        w = 1 << __lg(2*n-1);
        values.resize(2*w, identity_element(F));
        mutate.resize(2*w, identity_element(M));
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


struct mod_multiplies
{
    uint64_t operator() (uint64_t a, uint64_t b) { return a*b % MOD; }
} M;
struct bitwise_or
{
    uint64_t operator() (uint64_t a, uint64_t b) { return a | b; }
};

uint64_t identity_element(bitwise_or) { return 0; }
uint64_t identity_element(mod_multiplies) { return 1; }

struct pull_bit_or
{
    void operator() (size_t i, size_t nodeL, size_t nodeR,
                     vector<uint64_t>& values, vector<uint64_t>& mutate)
    {
        values[i] |= mutate[i];
        if(nodeL < nodeR)
        {
            mutate[2*i] |= mutate[i];
            mutate[2*i+1] |= mutate[i];
        }
        mutate[i] = 0;
    }
};

struct pull_mod_multiplies
{
    void operator() (size_t i, size_t nodeL, size_t nodeR,
                     vector<uint64_t>& values, vector<uint64_t>& mutate)
    {
        if(mutate[i] == 1) return;
        values[i] = M(values[i], power(mutate[i], nodeR - nodeL + 1, M));
        if(nodeL < nodeR)
        {
            mutate[2*i] = M(mutate[2*i], mutate[i]);
            mutate[2*i+1] = M(mutate[2*i+1], mutate[i]);
        }
        mutate[i] = 1;
    }
};

uint64_t identity_element(pull_bit_or) { return 0; }
uint64_t identity_element(pull_mod_multiplies) { return 1; }

using product_tree = segment_tree_i<
    uint64_t, mod_multiplies,
    uint64_t, pull_mod_multiplies, mod_multiplies
>;

using bitmask_tree = segment_tree_i<
    uint64_t, bitwise_or,
    uint64_t, pull_bit_or, bitwise_or
>;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    static bool is_composite[MAX_A + 1];
    vector<unsigned> primes;
    vector<uint64_t> pre;
    static vector<unsigned> factors_no[MAX_A + 1];
    for(size_t i = 2; i <= MAX_A; i++)
    {
        if(not is_composite[i])
        {
            factors_no[i].push_back(primes.size());
            for(size_t j = 2*i; j <= MAX_A; j += i)
            {
                is_composite[j] = true;
                factors_no[j].push_back(primes.size());
            }
            primes.push_back(i);
            pre.push_back(M(i - 1, power(i, MOD - 2, M)));
        }
    }

    size_t n, q;
    cin >> n >> q;

    product_tree T(n);
    bitmask_tree B(n);

    for(size_t i = 0; i < n; i++)
    {
        unsigned x;
        cin >> x;
        T.mut(i, i, x);
        uint64_t mask = 0;
        for(auto p : factors_no[x])
            mask |= (1ull << p);
        B.mut(i, i, mask);
    }

    while(q --> 0)
    {
        string c;
        cin >> c;
        if(c.front() == 'T')
        {
            size_t a, b;
            cin >> a >> b; a--; b--;

            uint64_t part = 1;
            auto mask = B.get(a, b);
            for(size_t p = 0; p < primes.size(); p++)
                if(mask & (1ull << p))
                    part = M(part, pre[p]);
            cout << M(T.get(a, b), part) << "\n";
        }
        else
        {
            size_t a, b; unsigned x;
            cin >> a >> b >> x; a--; b--;
            T.mut(a, b, x);
            uint64_t mask = 0;
            for(auto p : factors_no[x])
                mask |= (1ull << p);
            B.mut(a, b, mask);
        }
    }
}
