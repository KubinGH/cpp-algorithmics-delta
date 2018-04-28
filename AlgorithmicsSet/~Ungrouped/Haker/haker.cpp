#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500000, TSIZE = 1 << 20;

uint32_t maxs(uint32_t& p, uint32_t v)
{
    if(p < v)
        p = v;
}

struct interval_tree // interval-interval, set-max:max
{
    array<uint32_t, TSIZE> values, to_set;
    void pull(uint32_t i, uint32_t tbegin, uint32_t tend)
    {
        if(tbegin < tend and to_set[i] != 0)
        {
            maxs(to_set[2*i+1], to_set[i]);
            maxs(to_set[2*i+2], to_set[i]);
        }
        values[i] = max(to_set[i], values[i]);
        to_set[i] = 0;
    }
    void set(uint32_t i, uint32_t tbegin, uint32_t tend,
             uint32_t sbegin, uint32_t send, uint32_t value)
    {
        if(send < tbegin or tend < sbegin)
            return;
        else if(sbegin <= tbegin and tend <= send)
        {
            maxs(to_set[i], value);
            pull(i, tbegin, tend);
        }
        else
        {
            set(2*i+1, tbegin, (tbegin+tend)/2, sbegin, send, value);
            set(2*i+2, (tbegin+tend)/2+1, tend, sbegin, send, value);
            values[i] = max(values[2*i+1], values[2*i+2]);
        }
    }
    void set(uint32_t sbegin, uint32_t send, uint32_t value)
    {
        //cerr << "set " << sbegin << ".." << send << " <- " << value << endl;
        return set(0, 0, TSIZE/2-1, sbegin, send, value);
    }
    uint32_t get(uint32_t i, uint32_t tbegin, uint32_t tend,
                 uint32_t sbegin, uint32_t send)
    {
        if(to_set[i] != 0)
            pull(i, tbegin, tend);
        if(send < tbegin or tend < sbegin)
            return 0;
        else if(sbegin <= tbegin and tend <= send)
            return values[i];
        else
            return max(get(2*i+1, tbegin, (tbegin+tend)/2, sbegin, send),
                       get(2*i+2, (tbegin+tend)/2+1, tend, sbegin, send));
    }
    uint32_t get(uint32_t sbegin, uint32_t send)
    {
        return get(0, 0, TSIZE/2-1, sbegin, send);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> A;
    static array<uint32_t, MAX+1> S;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        S[i+1] = S[i] + A[i];
    }
    auto sum_cycled = [=](uint32_t a, uint32_t b) {
        if(a <= b)
            return S[b+1] - S[a];
        else
            return S[n] - (S[a] - S[b+1]);
    };
    static interval_tree tree;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t x = sum_cycled(i%n, (i+n/2-1)%n);
        //cerr << i << ": " << x << endl;
        if(i > 0)
        {
            if(i+n/2-1 < n)
                tree.set(0, i-1, x);
            else if((i+n/2-1)%n+1 <= i-1)
                tree.set((i+n/2-1)%n+1, i-1, x);
        }
        if(i+n/2-1 < n - 1)
            tree.set(i+n/2, n-1, x);
        //for(uint32_t i = 0; i < n; i++)
        //    cerr << tree.get(i, i) << " "; cerr << endl;
    }
    uint32_t m = -1u;
    for(uint32_t i = 0; i < n; i++)
        m = min(tree.get(i, i), m);
    cout << S[n] - m;
}
