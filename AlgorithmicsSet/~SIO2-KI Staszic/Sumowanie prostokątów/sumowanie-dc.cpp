#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e5;

struct rect_t
{
    uint32_t x1, y1, x2, y2;
    rect_t() {}
    rect_t(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) :
        x1(x1), y1(y1), x2(x2), y2(y2) {}
};
typedef tuple<bool, rect_t, uint32_t> query_t;

query_t queries[MAX];
uint32_t answers[MAX];

void solve(uint32_t ibegin, uint32_t iend)
{
    if(ibegin >= iend)
        return;
    uint32_t mid = (ibegin + iend) / 2;

}


int main()
{
    uint32_t q;
    cin >> q;
    for(uint32_t i = 0; i < q; i++)
    {
        uint32_t t, x1, y1, x2, y2;
        cin >> t >> x1 >> y1 >> x2 >> y2;
        get<0>(queries[i]) = t - 1;
        get<1>(queries[i]) = rect_t(x1, y1, x2, y2);
        if(t == 2)
            cin >> get<2>(queries[i]);
    }
    solve(0, q);
    for(uint32_t i = 0; i < q; i++)
        if(get<0>(queries[i]) == 1)
            cout << answers[i] << "\n";
}
