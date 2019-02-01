#include <bits/stdc++.h>

using namespace std;

struct occ { uint32_t x, c; };
inline occ minocc(occ a, occ b)
{
    if(a.x == b.x)
        return {a.x, a.c + b.c};
    else if(a.x < b.x)
        return a;
    else
        return b;
}
struct segment_tree
{
    uint32_t w;
    vector<occ> values;
    vector<int32_t> mutate;
    segment_tree(uint32_t n)
    {
        w = 1 << __lg(2*n-1);
        values.resize(2*w, {-1u, 0});
        mutate.resize(2*w);
        for(uint32_t i = 2*w; i --> w; )
            if(i-w < n) values[i] = {0, 1};
        for(uint32_t i = w; i --> 1; )
            values[i] = minocc(values[2*i], values[2*i+1]);
    }
    inline void pull(uint32_t i, uint32_t nodeL, uint32_t nodeR)
    {
        if(mutate[i] == 0) return;
        if(nodeL < nodeR)
        {
            mutate[2*i] += mutate[i];
            mutate[2*i+1] += mutate[i];
        }
        values[i].x += mutate[i];
        mutate[i] = 0;
    }
    occ get(uint32_t i, uint32_t nodeL, uint32_t nodeR, uint32_t queryL, uint32_t queryR)
    {
        if(nodeR < queryL or queryR < nodeL)
            return {-1u, 0};
        pull(i, nodeL, nodeR);
        if(queryL <= nodeL and nodeR <= queryR)
            return values[i];
        else
            return minocc(get(2*i, nodeL, (nodeL+nodeR)/2, queryL, queryR),
                          get(2*i+1, (nodeL+nodeR)/2+1, nodeR, queryL, queryR));
    }
    void mut(uint32_t i, uint32_t nodeL, uint32_t nodeR, uint32_t queryL, uint32_t queryR, int32_t value)
    {
        if(nodeR < queryL or queryR < nodeL)
            pull(i, nodeL, nodeR);
        else if(queryL <= nodeL and nodeR <= queryR)
        {
            mutate[i] += value;
            pull(i, nodeL, nodeR);
        }
        else
        {
            pull(i, nodeL, nodeR);
            mut(2*i, nodeL, (nodeL+nodeR)/2, queryL, queryR, value);
            mut(2*i+1, (nodeL+nodeR)/2+1, nodeR, queryL, queryR, value);
            values[i] = minocc(values[2*i], values[2*i+1]);
        }
    }
    occ get(uint32_t queryL, uint32_t queryR)
        { return get(1, 0, w-1, queryL, queryR); }
    void mut(uint32_t queryL, uint32_t queryR, int32_t value)
        { return mut(1, 0, w-1, queryL, queryR, value); }
    inline uint32_t last_min_ge(uint32_t p)
    {
        uint32_t i = 1, nodeL = 0, nodeR = w-1;
        pull(i, nodeL, nodeR);
        while(i < w)
        {
            i *= 2;
            uint32_t m = (nodeL+nodeR)/2;
            pull(i, nodeL, m); pull(i+1, m+1, nodeR);
            if(m >= p and values[i].x <= values[i+1].x)
                nodeR = m;
            else
                i++, nodeL = m+1;
        }
        return i - w;
    }
    inline uint32_t last_min_le(uint32_t p)
    {
        uint32_t i = 1, nodeL = 0, nodeR = w-1;
        pull(i, nodeL, nodeR);
        while(i < w)
        {
            i *= 2;
            uint32_t m = (nodeL+nodeR)/2;
            pull(i, nodeL, m); pull(i+1, m+1, nodeR);
            if(m+1 <= p and values[i].x >= values[i+1].x)
                i++, nodeL = m+1;
            else
                nodeR = m;
        }
        return i - w;
    }
};

inline int iabs(int x) { return x<0 ? -x : x; }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    vector<uint32_t> A(2*n);
    vector<list<uint32_t>> P(k);
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i]; A[i]--;
        P[A[i]].push_back(i);
    }
    copy(A.begin(), A.begin() + n, A.begin() + n);
    segment_tree T(2*n);
    for(uint32_t i = 0; i < k; i++)
        if(P[i].size() > 1)
            T.mut(P[i].front()+1, P[i].back(), 1);

    uint64_t total = 0; uint32_t best = n;
    for(uint32_t i = 0; i < n; i++)
    {
        occ o = T.get(i+1, i+n-1);
        if(o.x == 0) total += o.c;

        const uint32_t a = A[i];
        if(P[a].size() > 1)
            T.mut(P[a].front()+1, P[a].back(), -1);
        P[a].pop_front(); P[a].push_back(i + n);
        if(P[a].size() > 1)
            T.mut(P[a].front()+1, P[a].back(), 1);

        uint32_t e = T.last_min_le(i+n/2), f = T.last_min_ge(i+n/2+1);
        if(T.values[T.w+e].x == 0)
            best = min(best, (uint32_t)iabs(2*(e-i-1) - n));
        if(T.values[T.w+f].x == 0)
            best = min(best, (uint32_t)iabs(2*(f-i-1) - n));
    }
    total /= 2;
    cout << total << " " << best;
}
