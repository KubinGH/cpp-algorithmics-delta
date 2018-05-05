#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 5e5, TSIZE = 1 << 20;

struct segment_tree
{
    uint32_t values[TSIZE];
    void set(uint32_t i, uint32_t v)
    {
        i += TSIZE/2;
        values[i] = v;
        while(i > 1)
            i /= 2, values[i] = max(values[2*i], values[2*i+1]);
    }
    uint32_t find_latest_greater(uint32_t i)
    {
        i += TSIZE/2;
        uint32_t c = values[i];
        i /= 2;
        while(values[i] <= c)
            i /= 2;
        while(i < TSIZE/2)
        {
            if(values[2*i+1] > c)
                i *= 2, i++;
            else
                i *= 2;
        }
        return i - TSIZE/2;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t q;
    cin >> q;
    static uint32_t A[MAX];
    static pair<uint32_t, uint32_t> Q[MAX+1];
    for(uint32_t i = 0; i < q; i++)
        cin >> Q[i].first, A[i] = Q[i].first, Q[i].second = i;
    sort(Q, Q + q+1);
    unordered_map<uint32_t, uint32_t> T; T.reserve(2*q);
    for(uint32_t i = 0, f = 0; i < q+1; i++)
    {
        if(i > 0 and Q[i].first == Q[i-1].first)
            f++;
        T[Q[i].first] = i - f;
    }
    static uint32_t R[MAX+1];
    static segment_tree tree;
    tree.set(0, -1u);
    uint32_t t = 1;
    for(uint32_t qi = 0; qi < q; qi++)
    {
        uint32_t a = T[A[qi]];
        if(a > 0)
        {
            tree.set(t, a);
            R[t] = R[tree.find_latest_greater(t)] + 1;
            t++;
        }
        else
        {
            t--;
            tree.set(t, 0);
            R[t] = 0;
        }
        cout << R[t-1] << "\n";
    }
}
