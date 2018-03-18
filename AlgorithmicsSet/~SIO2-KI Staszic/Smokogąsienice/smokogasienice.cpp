#include <bits/stdc++.h>

using namespace std;

typedef uint64_t angle_t;

const size_t MAX = 1e6, PARTS = 1024;
angle_t MAX_ANGLE = 1LLU << 60;
const double TPI = acos(-1);

angle_t angle(double ax, double ay)
{
    return fmod(atan2(ay, ax) * (MAX_ANGLE/2) / TPI, MAX_ANGLE);
}
uint32_t part(angle_t a)
{
    return floor(a / (MAX_ANGLE / PARTS));
}


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t g, r;
    cin >> g >> r;
    static array<pair<angle_t, angle_t>, MAX> G;
    static array<vector<pair<angle_t, angle_t>>, PARTS> F;
    for(uint32_t i = 0; i < g; i++)
    {
        double x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        G[i].first = angle(x1, y1);
        G[i].second = angle(x2, y2);
        if(G[i].first > G[i].second)
            swap(G[i].first, G[i].second);
        for(uint32_t a = part(G[i].first); a <= part(G[i].second); a++)
        {
            F[a].emplace_back(G[i]);
        }
    }
    for(uint32_t i = 0; i < r; i++)
    {
        double x, y;
        cin >> x >> y;
        angle_t a = angle(x, y);
        uint32_t c = 0;
        for(pair<angle_t, angle_t> p : F[part(a)])
        {
            if(p.first <= a and a <= p.second)
                c++;
        }
        cout << c << " ";
    }
}
