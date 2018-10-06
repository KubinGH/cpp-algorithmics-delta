#include <bits/stdc++.h>

using namespace std;

int32_t sgn(int32_t x) { return x > 0 ? 1 : (x == 0 ? 0 : -1); }

template<typename Iterator, typename T = typename iterator_traits<Iterator>::value_type>
Iterator first_larger(Iterator first, Iterator last, T value)
    { return upper_bound(first, last, value); }
template<typename Iterator, typename T = typename iterator_traits<Iterator>::value_type>
Iterator last_smaller(Iterator first, Iterator last, T value)
    { return --lower_bound(first, last, value); }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<pair<int32_t, int32_t>> P(n);
    map<pair<int32_t, int32_t>, uint32_t> D;
    static vector<pair<int32_t, char>> X[1<<21], Y[1<<21];
    int32_t minx = 4e6, miny = 4e6;
    for(uint32_t i = 0; i < n; i++)
    {
        int32_t x, y;
        cin >> x >> y;
        P[i] = {x - y, x + y};
        minx = min(minx, x - y);
        miny = min(miny, x + y);
    }
    for(uint32_t i = 0; i < n; i++)
        P[i].first -= minx, P[i].second -= miny, D[P[i]] = i;
    {
        int32_t cx = P[n-1].first, cy = P[n-1].second;
        int32_t ldx = sgn(P[n-1].first - P[n-2].first);
        for(uint32_t i = 0; i < n; i++)
        {
            int32_t dx = sgn(P[i].first - cx), dy = sgn(P[i].second - cy);
            bool first = true;
            char d = (dx == dy) ? 'N' : 'Z'; // top-left to bot-right or bot-left to top-right
            while(cx != P[i].first or cy != P[i].second)
            {
                if(first)
                {
                    if(dx == ldx)
                        X[cx].emplace_back(cy, ' ');
                    else
                        Y[cy].emplace_back(cx, ' ');
                }
                else
                {
                    X[cx].emplace_back(cy, d);
                    Y[cy].emplace_back(cx, d);
                }
                first = false;
                cx += dx; cy += dy;
            }
            ldx = dx;
        }
    }
    for(auto& p : X) sort(p.begin(), p.end());
    for(auto& p : Y) sort(p.begin(), p.end());
    vector<bool> bound(n);
    cout << n/2 << "\n";
    for(uint32_t i = 0; i < n; i++)
    {
        if(bound[i]) continue;
        uint32_t o = -1u;
        auto ap = i==0 ? P[n-1] : P[i-1];
        auto bp = i==n-1 ? P[0] : P[i+1];
        int32_t fx = sgn(P[i].first - ap.first), fy = sgn(P[i].second - ap.second);
        int32_t gx = sgn(bp.first - P[i].first), gy = sgn(bp.second - P[i].second);
        int32_t dx = 0, dy = 0;
        if     ((fx == 1 and fy == -1 and gx == 1 and gy == 1) or
                (fx == 1 and fy == 1 and gx == 1 and gy == -1))
            dx = 0, dy = -2;
        else if((fx == 1 and fy == -1 and gx == -1 and gy == -1) or
                (fx == -1 and fy == -1 and gx == 1 and gy == -1))
            dx = -2, dy = 0;
        else if((fx == 1 and fy == 1 and gx == -1 and gy == 1) or
                (fx == -1 and fy == 1 and gx == 1 and gy == 1))
            dx = 2, dy = 0;
        else if((fx == -1 and fy == 1 and gx == -1 and gy == -1) or
                (fx == -1 and fy == -1 and gx == -1 and gy == 1))
            dx = 0, dy = 2;
        int32_t cx = P[i].first, cy = P[i].second;
        bool done = false;
        while(not done)
        {
            if(dx > 0)
            {
                auto it = first_larger(Y[cy].begin(), Y[cy].end(), {cx, CHAR_MAX});
                if(it->second == 'N') { dx = 0; dy = 2; }
                else if(it->second == 'Z') { dx = 0; dy = -2; }
                else if(it->second == ' ') { done = true; }
                cx = it->first;
            }
            else if(dx < 0)
            {
                auto it = last_smaller(Y[cy].begin(), Y[cy].end(), {cx, 0});
                if(it->second == 'N') { dx = 0; dy = -2; }
                else if(it->second == 'Z') { dx = 0; dy = 2; }
                else if(it->second == ' ') { done = true; }
                cx = it->first;
            }
            else if(dy > 0)
            {
                auto it = first_larger(X[cx].begin(), X[cx].end(), {cy, CHAR_MAX});
                if(it->second == 'N') { dx = 2; dy = 0; }
                else if(it->second == 'Z') { dx = -2; dy = 0; }
                else if(it->second == ' ') { done = true; }
                cy = it->first;
            }
            else if(dy < 0)
            {
                auto it = last_smaller(X[cx].begin(), X[cx].end(), {cy, 0});
                if(it->second == 'N') { dx = -2; dy = 0; }
                else if(it->second == 'Z') { dx = 2; dy = 0; }
                else if(it->second == ' ') { done = true; }
                cy = it->first;
            }
        }
        o = D[{cx, cy}];
        bound[i] = true; bound[o] = true;
        cout << i+1 << " " << o+1 << "\n";
    }
}
