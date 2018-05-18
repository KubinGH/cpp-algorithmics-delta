#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e6, TSIZE = 1 << 21;

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
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static segment_tree occurence;
    static uint32_t last_occured[MAX+1];
    fill(begin(last_occured), end(last_occured), -1u);
    uint32_t r = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a;
        cin >> a;
        if(last_occured[a] != -1u)
            occurence.set(a, last_occured[a] + 1);
        last_occured[a] = i;
        r = max(r, i - occurence.values[1] + 1);
    }
    cout << r;
}
