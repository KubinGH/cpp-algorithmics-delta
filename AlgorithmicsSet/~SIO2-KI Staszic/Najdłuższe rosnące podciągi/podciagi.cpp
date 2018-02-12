#include <bits/stdc++.h>
#define ALLOW_EQUAL 0

using namespace std;

typedef uint32_t(*tree_func)(uint32_t a, uint32_t b);

const size_t MAX = 500000;
const size_t TSIZE = 1 << 20;

template<tree_func F>
struct interval_tree
{
    array<uint32_t, TSIZE> values, settime;
    uint32_t ctime = 0;
    void set_value(uint32_t i, uint32_t value)
    {
        i += TSIZE/2 - 1;
        values[i] = value;
        settime[i] = ctime;
        while(i)
        {
            i = (i-1)/2,
            values[i] = F(settime[2*i+1] == ctime ? values[2*i+1] : 0,
                          settime[2*i+2] == ctime ? values[2*i+2] : 0);
            settime[i] = ctime;
        }
    }
    uint32_t find_value(uint32_t i, uint32_t tbegin, uint32_t tend, uint32_t sbegin, uint32_t send)
    {
        if(tend < sbegin or send < tbegin)
            return 0;
        else if(sbegin <= tbegin and tend <= send)
            return settime[i] == ctime ? values[i] : 0;
        else
            return F(find_value(2*i+1, tbegin, (tbegin+tend)/2, sbegin, send),
                     find_value(2*i+2, (tbegin+tend)/2+1, tend, sbegin, send));
    }
    uint32_t find_value(uint32_t sbegin, uint32_t send)
    {
        return find_value(0, 0, TSIZE/2-1, sbegin, send);
    }
};

/*
20 100
22 22 43 33 14 70 29 19 15 42 6 27 68 69 20 21 21 88 16 53 13
*/

uint32_t mod;

uint32_t max(uint32_t a, uint32_t b)
{
    return a > b ? a : b;
}
uint32_t add_wmod(uint32_t a, uint32_t b)
{
    return (a + b) % mod;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n >> mod;
    if(mod == 1)
    {
        cout << 0; return 0;
    }
    pair<uint32_t, uint32_t>* B = new pair<uint32_t, uint32_t>[n];
    for(uint32_t i = 0; i < n; i++)
        cin >> B[i].first, B[i].second = i;
    sort(B, B + n);
    static array<uint32_t, MAX> A;
    for(uint32_t i = 0, f = 0; i < n; i++)
    {
        if(i > 0 and B[i].first == B[i-1].first)
            f++;
        A[B[i].second] = i - f;
    }
    delete[] B;
    static interval_tree<max> tree;
    static array<uint32_t, MAX> P;
    static array<vector<uint32_t>, MAX+1> V;
    uint32_t m = 0;
    for(uint32_t i = 0; i < n; i++)
    {
#if ALLOW_EQUAL == 1
        P[i] = tree.find_value(0, A[i]) + 1;
#else
        P[i] = max((A[i] > 0 ? tree.find_value(0, A[i]-1) : 0u), 0u) + 1;
#endif
        if(P[i] > tree.values[A[i] + TSIZE/2 - 1])
            tree.set_value(A[i], P[i]);
        V[P[i]].push_back(i);
        if(P[i] > m) m = P[i];
    }
    static array<uint32_t, MAX> C;
    static interval_tree<add_wmod> count_tree;
    for(uint32_t p = 1; p < m + 1; p++)
    {
        if(p == 1)
        {
            for(uint32_t i : V[p])
                C[i] = 1;
            continue;
        }
        uint32_t i = 0, j = 0, a = V[p][0], b = V[p-1][0];
        count_tree.ctime = p;
        while(i < V[p].size() or j < V[p-1].size())
        {
            if(j >= V[p-1].size() or (i < V[p].size() and a < b))
            {
                C[a] = count_tree.find_value(0, A[a]-1);
                i++;
                a = V[p][i];
            }
            else
            {
                uint32_t c = (C[b] + count_tree.values[TSIZE/2+A[b]-1]) % mod;
                count_tree.set_value(A[b], c);
                j++;
                b = V[p-1][j];
            }
        }
    }
    uint32_t r = 0;
    for(uint32_t i : V[m])
        r += C[i], r %= mod;
    cout << r;
}
