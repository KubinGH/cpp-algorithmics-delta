#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000, MAX_D = 16000, TSIZE = 1 << 15;

struct segment_tree
{
    uint32_t values[TSIZE];
    void set(uint32_t i, uint32_t x)
    {
        //cout << "set " << i << " <- " << x << endl;
        i += TSIZE/2;
        values[i] = x;
        while(i > 1)
            i /= 2, values[i] = min(values[2*i], values[2*i+1]);
    }
    uint32_t get(uint32_t i, uint32_t tbegin, uint32_t tend,
                             uint32_t sbegin, uint32_t send)
    {
        //cout << "get " << i << " " << tbegin << ".." << tend << " " << sbegin << ".." << send << " [" << values[i] << "]" << endl;
        if(tend < sbegin or send < tbegin)
            return -1u;
        else if(sbegin <= tbegin and tend <= send)
            return values[i];
        else
            return min(get(2*i,   tbegin, (tbegin+tend)/2, sbegin, send),
                       get(2*i+1, (tbegin+tend)/2+1, tend, sbegin, send));
    }
    uint32_t get(uint32_t sbegin, uint32_t send)
        { return get(1, 0, TSIZE/2-1, sbegin, send); }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t d, n;
    cin >> d >> n;
    static segment_tree tree;
    fill(tree.values, tree.values + TSIZE, -1u);
    tree.set(0, 0);
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t p, c;
        cin >> p >> c;
        uint32_t x = c + tree.get(p - min(p, 800u), p);
        if(x < tree.values[TSIZE/2 + p])
        {
            tree.set(p, x);
        }
    }
    cout << tree.get(d - min(d, 800u), d);
}
