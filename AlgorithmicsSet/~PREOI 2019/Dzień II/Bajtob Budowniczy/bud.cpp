#include <bits/stdc++.h>

using namespace std;

struct segment_tree
{
    uint32_t w;
    vector<uint32_t> values, mutate;
    segment_tree(uint32_t n)
    {
        w = 1 << __lg(2*n-1);
        values.resize(2*w); mutate.resize(2*w);
    }
    inline void pull(uint32_t i, uint32_t nodeL, uint32_t nodeR)
    {
        // require x != 0
        if(not mutate[i]) return;
        if(nodeL < nodeR)
        {
            values[i] = 0;
            mutate[2*i] = mutate[i];
            mutate[2*i+1] = mutate[i];
        }
        else
            values[i] = mutate[i];
        mutate[i] = 0;
    }
    inline void set(uint32_t i, uint32_t value)
    {
        values[w + i] = value;
    }
    inline void build()
    {
        for(uint32_t i = w; i --> 1; )
            values[i] = values[2*i] ^ values[2*i+1];
    }
    uint32_t get(uint32_t i, uint32_t nodeL, uint32_t nodeR, uint32_t queryL, uint32_t queryR)
    {
        pull(i, nodeL, nodeR);
        if(nodeR < queryL or queryR < nodeL)
            return 0;
        else if(queryL <= nodeL and nodeR <= queryR)
            return values[i];
        else
            return get(2*i, nodeL, (nodeL+nodeR)/2, queryL, queryR) ^
                   get(2*i+1, (nodeL+nodeR)/2+1, nodeR, queryL, queryR);
    }
    void mut(uint32_t i, uint32_t nodeL, uint32_t nodeR, uint32_t queryL, uint32_t queryR, uint32_t value)
    {
        pull(i, nodeL, nodeR);
        if(nodeR < queryL or queryR < nodeL)
            ;
        else if(queryL <= nodeL and nodeR <= queryR)
        {
            mutate[i] = value;
            pull(i, nodeL, nodeR);
        }
        else
        {
            mut(2*i, nodeL, (nodeL+nodeR)/2, queryL, queryR, value);
            mut(2*i+1, (nodeL+nodeR)/2+1, nodeR, queryL, queryR, value);
            values[i] = values[2*i] ^ values[2*i+1];
        }
    }
    inline uint32_t get(uint32_t queryL, uint32_t queryR) { return get(1, 0, w-1, queryL, queryR); }
    inline void mut(uint32_t queryL, uint32_t queryR, uint32_t value) { return mut(1, 0, w-1, queryL, queryR, value); }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    segment_tree T(n);
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t x;
        cin >> x;
        T.set(i, x);
    }
    T.build();
    while(q --> 0)
    {
        uint32_t a, b;
        bool t;
        cin >> t >> a >> b; a--; b--;
        if(t == 0)
        {
            uint32_t x;
            cin >> x;
            T.mut(a, b, x);
        }
        else if(t == 1)
            cout << T.get(a, b) << "\n";
    }
}
