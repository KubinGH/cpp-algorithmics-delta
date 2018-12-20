#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 18;

enum setops_types { None = 0, Set0 = 1, Set1 = 2 };
struct bin_segment_bush
{
    static constexpr size_t w = 1 << 17;
    uint32_t values[MAX];
    setops_types mutate[MAX];
    bin_segment_bush()
    {
        fill(values, values + 2*w, 0);
        fill(mutate, mutate + 2*w, None);
    }
    void pull(size_t i, size_t nodeL, size_t nodeR)
    {
        if(mutate[i] == None) return;
        if(i < w)
        {
            mutate[2*i] = mutate[i];
            mutate[2*i+1] = mutate[i];
        }
        values[i] = mutate[i] == Set1 ? nodeR - nodeL + 1 : 0;
        mutate[i] = None;
    }
    uint32_t get(size_t i, size_t nodeL, size_t nodeR, size_t getL, size_t getR)
    {
        pull(i, nodeL, nodeR);
        if(nodeR < getL or nodeL > getR)
            return 0;
        else if(getL <= nodeL and nodeR <= getR)
            return values[i];
        else
            return get(2*i, nodeL, (nodeL+nodeR)/2, getL, getR) +
                   get(2*i+1, (nodeL+nodeR)/2+1, nodeR, getL, getR);
    }
    uint32_t get(size_t getL, size_t getR) { return get(1, 0, w-1, getL, getR); }
    void mut0(size_t i, size_t nodeL, size_t nodeR, size_t getL, size_t getR)
    {
        if(getL <= nodeL and nodeR <= getR)
        {
            if(i < w)
            {
                mutate[2*i] = Set0;
                mutate[2*i+1] = Set0;
            }
            values[i] = 0;
            mutate[i] = None;
        }
        else if(nodeL <= getR and getL <= nodeR)
        {
            pull(i, nodeL, nodeR);
            mut0(2*i, nodeL, (nodeL+nodeR)/2, getL, getR);
            mut0(2*i+1, (nodeL+nodeR)/2+1, nodeR, getL, getR);
            values[i] = values[2*i] + values[2*i+1];
        }
    }
    void mut0(size_t getL, size_t getR) { return mut0(1, 0, w-1, getL, getR); }
    void mut1(size_t i, size_t nodeL, size_t nodeR, size_t getL, size_t getR)
    {
        if(getL <= nodeL and nodeR <= getR)
        {
            if(i < w)
            {
                mutate[2*i] = Set1;
                mutate[2*i+1] = Set1;
            }
            values[i] = nodeR - nodeL + 1;
            mutate[i] = None;
        }
        else if(nodeL <= getR and getL <= nodeR)
        {
            pull(i, nodeL, nodeR);
            mut1(2*i, nodeL, (nodeL+nodeR)/2, getL, getR);
            mut1(2*i+1, (nodeL+nodeR)/2+1, nodeR, getL, getR);
            values[i] = values[2*i] + values[2*i+1];
        }
    }
    void mut1(size_t getL, size_t getR) { return mut1(1, 0, w-1, getL, getR); }
};

struct query_t
{
    uint32_t L, R; bool t;
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    static int32_t A[MAX];
    for(uint32_t i = 0; i < n; i++)
    {
        int32_t a;
        cin >> a;
        A[i] = a;
    }
    static query_t queries[MAX];
    for(uint32_t i = 0; i < q; i++)
    {
        cin >> queries[i].L >> queries[i].R >> queries[i].t;
        queries[i].L--; queries[i].R--;
    }
    static int32_t E[MAX];
    copy(A, A + n, E);
    sort(E, E + n);
    uint32_t m = unique(E, E + n) - E;
    uint32_t lo = 0, hi = m;
    static bin_segment_bush Ts[20]; uint32_t t = 0;
    while(lo < hi)
    {
        uint32_t mid = (lo + hi) / 2;
        bin_segment_bush& T = Ts[t++];
        for(uint32_t i = n; i --> 0; )
            T.values[T.w + i] = A[i] > E[mid];
        for(uint32_t i = T.w; i --> 1; )
            T.values[i] = T.values[2*i] + T.values[2*i+1];
        for(uint32_t i = 0; i < q; i++)
        {
            uint32_t L = queries[i].L, R = queries[i].R;
            uint32_t c = T.get(L, R);
            if(queries[i].t)
            {
                T.mut1(L, L+c-1);
                T.mut0(L+c, R);
            }
            else
            {
                c = (R - L + 1) - c;
                T.mut0(L, L+c-1);
                T.mut1(L+c, R);
            }
        }
        if(T.get(n/2, n/2) == 0)
            hi = mid;
        else
            lo = mid+1;
    }
    cout << E[lo];
}
