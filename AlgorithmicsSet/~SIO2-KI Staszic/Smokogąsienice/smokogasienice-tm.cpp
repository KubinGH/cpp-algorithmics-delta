#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 5e5;
double MAX_ANGLE = 360;
const double TPI = acos(-1);
const int32_t INF_I32 = numeric_limits<int32_t>::max();

double angle(double ax, double ay)
{
    return fmod(atan2(ay, ax) * (MAX_ANGLE/2) / TPI, MAX_ANGLE);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t g, r;
    cin >> g >> r;
    vector<pair<double, int32_t>> events;
    for(uint32_t i = 0; i < g; i++)
    {
        double x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        double a = angle(x1, y1), b = angle(x2, y2);
        if(a > b) swap(a, b);
        events.emplace_back(a, -INF_I32);
        events.emplace_back(b, INF_I32);
    }
    for(uint32_t i = 0; i < r; i++)
    {
        double x, y;
        cin >> x >> y;
        events.emplace_back(angle(x, y), i);
    }
    sort(events.begin(), events.end());
    static array<uint32_t, MAX> results;
    uint32_t current = 0;
    for(pair<double, int32_t> event : events)
    {
        int32_t t = event.second;
        if(t == -INF_I32)
            current++;
        else if(t == INF_I32)
            current--;
        else
            results[t] = current;
    }
    for(uint32_t i = 0; i < r; i++)
        cout << results[i] << " ";
}
