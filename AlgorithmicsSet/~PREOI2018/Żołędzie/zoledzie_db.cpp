#include <bits/stdc++.h>
#define FAIL { ok = false; goto after;}

using namespace std;

typedef pair<int64_t, int64_t> pair_i64;

const size_t MAX = 1000000;
const double MK_PI = 3.141592653589793238462643383279502884L;
const double PRECISION = 1 << 20;

double dround(double n, double p = PRECISION)
{
    double r = round(n * p) / p;
    if(r == -0) r = 0;
    return r;
}

double vangle(int64_t x, int64_t y)
{
    double r = dround(atan2(y, x) / MK_PI * 180) + 180;
    if(r == 360)
        return 0;
    else
        return r;
}

double vangle(pair_i64 p)
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
    static array<double, MAX> A1, A2;
    unordered_map<int64_t, multiset<double> > H1, H2;
    unordered_set<int64_t> K1, K2;
    multiset<double> B;
    multiset<double>::iterator it;
    unordered_set<double> U;
    bool ok = true;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> P1[i].first >> P1[i].second;
        H1[hypotsq(P1[i])].insert(vangle(P1[i]));
        K1.insert(hypotsq(P1[i]));
    }
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> P2[i].first >> P2[i].second;
        H2[hypotsq(P2[i])].insert(vangle(P2[i]));
        K2.insert(hypotsq(P2[i]));
    }
    double s1 = 0, s2 = 0;
    if(K1.size() != K2.size()) FAIL;
    for(int64_t k : K1)
        if(H1[k].size() != H2[k].size())
            FAIL;
    H1.erase(0); H2.erase(0); K1.erase(0); K2.erase(0);
    sort(P1.begin(), P1.begin() + n, angle_less);
    sort(P2.begin(), P2.begin() + n, angle_less);
    for(uint32_t i = 0; i < n; i++)
        A1[i] = vangle(P1[i]), A2[i] = vangle(P2[i]);
    for(uint32_t i = 0; i < n; i++)
        s1 += A1[i], s2 += A2[i];
    ok = false;
    for(uint32_t x = 0; x < n + 5; x++)
    {
        s2 += 360;
        double r;
        if(x < n + 1) r = fmod(dround((s2 - s1) / n), 360);
        else if(x == n + 1) r = 90;
        else if(x == n + 2) r = 180;
        else if(x == n + 3) r = 270;
        else r = 360;
        bool pok = true;
        if(U.find(r) != U.end() and x < n) { x = n; continue; }
        else U.insert(r);
        //cout << r << endl;
        for(int64_t k : K1)
        {
            B = H2[k];
            //cout << k << ": ";
            //for(double b : B)
            //    cout << b << ", "; cout << endl;
            for(double a : H1[k])
            {
                it = B.find(dround(fmod(a + r, 360)));
                //cout << a << " " << dround(fmod(a + r, 360)) << endl;
                if(it != B.end())
                    B.erase(it);
                else
                {
                    pok = false; break;
                }
            }
            if(B.size())
            {
                pok = false; break;
            }
        }
        if(pok)
        {
            ok = true; break;
        }
    }
    /*if(not ok)
    {
        for(uint32_t i = 0; i < n; i++)
            cout << P1[i].first << "_" << P1[i].second << ";";
        cout << "|";
        for(uint32_t i = 0; i < n; i++)
            cout << P2[i].first << "_" << P2[i].second << ";";
    }*/
after:
    cout << (ok ? "TAK" : "NIE");
}
