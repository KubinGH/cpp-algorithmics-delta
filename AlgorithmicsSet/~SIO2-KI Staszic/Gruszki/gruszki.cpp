#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e5, TSIZE = 1 << 18;

struct segment_tree
{
    uint32_t values[TSIZE];
    void build()
    {
        for(uint32_t i = TSIZE/2 - 1; i --> 0;)
            values[i] = max(values[2*i+1], values[2*i+2]);
    }
    uint32_t find_first_greater_or_equal(uint32_t x)
    {
        uint32_t i = 0;
        if(x > values[0])
            return -1u;
        while(i < TSIZE/2 - 1)
        {
            if(values[2*i+1] >= x)
                i = 2*i+1;
            else
                i = 2*i+2;
        }
        return i;
    }
    void set(uint32_t i, uint32_t x)
    {
        values[i] = x;
        while(i > 0)
        {
            i--, i /= 2;
            values[i] = max(values[2*i+1], values[2*i+2]);
        }
    }
};


int main()
{
    uint32_t n;
    cin >> n;
    static segment_tree T;
    for(uint32_t i = 0; i < n; i++)
        cin >> T.values[TSIZE/2-1+i];
    T.build();
    uint32_t m;
    cin >> m;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t a;
        cin >> a;
        if(a > T.values[0])
            cout << "-1 ";
        else
        {
            uint32_t t = T.find_first_greater_or_equal(a);
            T.set(t, T.values[t] - a);
            cout << t - TSIZE/2 + 2 << " ";
        }
    }
}
