#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 2e5, TSIZE = 1 << 20;

typedef unsigned int uint32_t;

struct dt
{
    char c; uint32_t a, b;
    dt() { c = 0; a = 0; b = 0; }
    dt(char _c, uint32_t _a, uint32_t _b) { c = _c; a = _a; b = _b; }
};

// set1-sum tree
struct segment_tree
{
    uint32_t values[TSIZE]; bool to_set[TSIZE];
    void push(uint32_t i, uint32_t tbegin, uint32_t tend)
    {
        if(not to_set[i])
            return;
        else if(values[i] == tend - tbegin + 1)
        {
            to_set[i] = false;
            return;
        }
        values[i] = tend - tbegin + 1;
        if(tbegin < tend)
        {
            to_set[2*i]   = true;
            to_set[2*i+1] = true;
        }
        to_set[i] = false;
    }

    void set(uint32_t i, uint32_t tbegin, uint32_t tend,
                         uint32_t sbegin, uint32_t send)
    {
        push(i, tbegin, tend);
        if(tend < sbegin or send < tbegin)
            return;
        else if(sbegin <= tbegin and tend <= send)
        {
            to_set[i] = true;
            push(i, tbegin, tend);
        }
        else
        {
            set(2*i,   tbegin, (tbegin+tend)/2, sbegin, send);
            set(2*i+1, (tbegin+tend)/2+1, tend, sbegin, send);
            values[i] = values[2*i] + values[2*i+1];
        }
    }

    void set(uint32_t sbegin, uint32_t send)
        { return set(1, 0, TSIZE/2-1, sbegin, send); }

    uint32_t get(uint32_t i, uint32_t tbegin, uint32_t tend,
                             uint32_t sbegin, uint32_t send)
    {
        push(i, tbegin, tend);
        if(tend < sbegin or send < tbegin)
            return 0;
        else if(sbegin <= tbegin and tend <= send)
            return values[i];
        else
            return get(2*i,   tbegin, (tbegin+tend)/2, sbegin, send) +
                   get(2*i+1, (tbegin+tend)/2+1, tend, sbegin, send);
    }

    uint32_t get(uint32_t sbegin, uint32_t send)
        { return get(1, 0, TSIZE/2-1, sbegin, send); }

    bool iszero(uint32_t i, uint32_t tbegin, uint32_t tend,
                            uint32_t sbegin, uint32_t send)
    {
        push(i, tbegin, tend);
        if(tend < sbegin or send < tbegin)
            return true;
        else if(sbegin <= tbegin and tend <= send)
            return values[i] == 0;
        else
            return iszero(2*i,   tbegin, (tbegin+tend)/2, sbegin, send) and
                   iszero(2*i+1, (tbegin+tend)/2+1, tend, sbegin, send);
    }

    bool iszero(uint32_t sbegin, uint32_t send)
        { return iszero(1, 0, TSIZE/2-1, sbegin, send); }
};

int main()
{
    uint32_t n, m;
    scanf("%u %u", &n, &m);
    static dt events[MAX];
    static pair<uint32_t, uint32_t> values[2*MAX];
    for(uint32_t i = 0; i < m; i++)
    {
        char c; uint32_t a, b;
        scanf(" %c %u %u", &c, &a, &b);
        events[i] = dt(c, a, b);
        values[2*i].first  = a;
        values[2*i].second = 2*i;
        values[2*i+1].first  = b;
        values[2*i+1].second = 2*i+1;
    }
    sort(values, values + 2*m);
    for(uint32_t i = 0, f = 0; i < 2*m; i++)
    {
        if(i > 0 and values[i].first == values[i-1].first)
            f++;
        if(values[i].second%2 == 0)
            events[values[i].second/2].a = i - f;
        else
            events[values[i].second/2].b = i - f;

    }
    static segment_tree tree;
    for(uint32_t i = 0; i < m; i++)
    {
        if(events[i].c == 'U')
            tree.set(events[i].a, events[i].b);
        else if(events[i].c == 'Z')
            printf(tree.iszero(events[i].a, events[i].b)
                   ? "TAK\n" : "NIE\n");
    }
}
