#include <bits/stdc++.h>

using namespace std;

struct point { int32_t x, y, z; };
bool operator< (const point& lhs, const point& rhs)
{
    if(lhs.x == rhs.x)
    {
        if(lhs.y == rhs.y)
            return lhs.z < rhs.z;
        else
            return lhs.y < rhs.y;
    }
    else
        return lhs.x < rhs.x;
}
bool strong_less(const point& lhs, const point& rhs)
{
    return lhs.x < rhs.x and lhs.y < rhs.y and lhs.z < rhs.z;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<point> P(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> P[i].x >> P[i].y >> P[i].z;
    vector<uint32_t> R; R.reserve(n);
    for(uint32_t i = 0; i < n; i++)
    {
        bool ok = true;
        for(uint32_t j = 0; j < n and ok; j++) if(i != j)
            if(strong_less(P[j], P[i]))
                ok = false;
        if(ok)
            R.push_back(i);
    }
    cout << R.size() << "\n";
    for(uint32_t i : R)
        cout << i+1 << " ";
}
