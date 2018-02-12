#include <bits/stdc++.h>
#define FAIL { ok = false; goto after;}

using namespace std;

typedef pair<int64_t, int64_t> pair_i64;

const size_t MAX = 1000000;
const double MK_PI = 3.141592653589793238462643383279502884L;
const double PRECISION = 1 << 20;

double dround(double n, double p = PRECISION)
{
    //double r = round(n * p) / p;
    //if(r == -0) r = 0;
    return n;
}

uint16_t vangle(int64_t x, int64_t y)
{
    //double r = dround(atan2(y, x) / MK_PI * 180) + 180;
    //if(r == 360)
    //    return 0;
    //else
    //    return r;
    return round((dround(atan2(y, x) / MK_PI * 180) + 180) / 360 * (1 << 16));
}

uint16_t vangle(pair_i64 p)
{
    return vangle(p.first, p.second);
}


bool angle_less(pair_i64 a, pair_i64 b)
{
    return vangle(a) < vangle(b);
}

int64_t hypotsq(pair_i64 p)
{
    return p.first * p.first + p.second * p.second;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<pair_i64, MAX> P1, P2;
    unordered_map<int64_t, vector<uint16_t> > H1;
    unordered_map<int64_t, multiset<uint16_t> > H2;
    vector<int64_t> K1, K2;
    multiset<uint16_t> B;
    multiset<uint16_t>::iterator it;
    unordered_set<uint16_t> U;
    bool ok = true;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> P1[i].first >> P1[i].second;
        H1[hypotsq(P1[i])].push_back(vangle(P1[i]));
        K1.push_back(hypotsq(P1[i]));
    }
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> P2[i].first >> P2[i].second;
        H2[hypotsq(P2[i])].insert(vangle(P2[i]));
        K2.push_back(hypotsq(P2[i]));
    }
    uint32_t s1 = 0, s2 = 0;
    if(K1.size() != K2.size()) FAIL;
    for(int64_t k : K1)
        if(H1[k].size() != H2[k].size())
            FAIL;
    for(uint32_t i = 0; i < n; i++)
        s1 += vangle(P1[i]), s2 += vangle(P2[i]);
    ok = false;
    for(uint32_t x = 0; x < n + 5; x++)
    {
        s2 += 1 << 16;
        uint16_t r;
        if(x < n + 1) r = ((s2 - s1) / n) % (1 << 16);
        else if(x == n + 1) r = 1 << 14;
        else if(x == n + 2) r = 1 << 15;
        else if(x == n + 3) r = 49152;
        else r = (1u << 16) - 1;
        bool pok = true;
        if(U.find(r) != U.end() and x < n) { x = n; continue; }
        else U.insert(r);
        for(int64_t k : K1)
        {
            if(k == 0) continue;
            B = H2[k];
            for(uint16_t a : H1[k])
            {
                it = B.find(a + r);
                if(it != B.end())
                    B.erase(it);
                else
                {
                    pok = false; break;
                }
            }
            if(not B.empty())
            {
                pok = false; break;
            }
        }
        if(pok)
        {
            ok = true; break;
        }
    }
after:
    cout << (ok ? "TAK" : "NIE");
}
