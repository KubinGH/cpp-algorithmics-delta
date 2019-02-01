#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

vector<int64_t> zeckendorf(int64_t x, const vector<int64_t>& F)
{
    vector<int64_t> R;
    for(uint32_t i = F.size(); i --> 0;)
        if(F[i] and x >= F[i])
            x -= F[i], R.push_back(F[i]);
    return R;
}

vector<int64_t> mod_zeckendorf(int64_t x, const vector<int64_t>& F)
{
    if(x == 0) return {};
    vector<int64_t> R;
    for(uint32_t i = 0; i < F.size(); i++)
      for(uint32_t j = i; j < F.size(); j++)
    {
        vector<int64_t> T = zeckendorf(x + F[i] + F[j], F);
        if(F[i]) T.push_back(-F[i]); if(F[j]) T.push_back(-F[j]);
        sort(T.begin(), T.end(), [&](int64_t a, int64_t b) {
            return abs(a) > abs(b) or (abs(a) == abs(b) and a > b);
        });
        if(R.empty() or R.size() > T.size())
            R = T;
    }
    return R;
}


pair<bool, vector<int64_t>> _reway(int64_t x, const vector<int64_t>& F,
                                   uint32_t i, bool nonzero = false)
{
    //cout << x << " ; " << i << " " << nonzero << endl;
    //cout << "> " << i << ": " << F[i] << endl;

    if(i <= 1 or x == 0)
        return {x == 0, {}};
    vector<int64_t> t;

    bool c1 = x - F[i] + F[i-1] - 1 >= 0, c2 = x + F[i] - F[i-1] + 1 <= 0;

    if(not c1 and not c2)
        nonzero = false;

    if(c1)
    {
        auto v = _reway(x - F[i], F, i - 2);
        if(v.first and (t.empty() or t.size() > v.second.size()+1))
            { t = v.second; t.push_back(F[i]); }
    }

    if(c2)
    {
        auto v = _reway(x + F[i], F, i - 2);
        if(v.first and (t.empty() or t.size() > v.second.size()+1))
            { t = v.second; t.push_back(-F[i]); }
    }

    {
        auto v = _reway(x, F, i - 1, true);
        if(v.first and (t.empty() or t.size() > v.second.size()))
            { t = v.second; }
    }

    return {not t.empty(), t};
}

vector<int64_t> reway(int64_t x, const vector<int64_t>& F)
{
    if(x == 0) return {};
    if(x <= 3) return {x};
    uint32_t m = upper_bound(F.begin(), F.end(), x) - F.begin();
    cout << x << " -> " << m << ": " << F[m] << endl;
    for(uint32_t i = 0; i <= m; i++)
        cout << F[i] << " "; cout << endl;
    auto r1 = _reway(x - F[m], F, m - 2); r1.second.push_back(F[m]);
    auto r2 = _reway(x - F[m-1], F, m - 3); r2.second.push_back(F[m-1]);
    vector<int64_t> t;
    if(r1.first and r2.first)
        t = r1.second.size() < r2.second.size() ? r1.second : r2.second;
    else
        t = r1.first ? r1.second : r2.second;
    reverse(t.begin(), t.end());
    return t;
}

uint32_t gamma(int64_t x, const vector<int64_t>& F)
{
    if(x == 0) return 0;
    if(x <= 3) return 1;
    uint32_t m = upper_bound(F.begin(), F.end(), x) - F.begin();
    return min(gamma(x - F[m-1], F), gamma(F[m] - x, F));
}

int main()
{
    vector<int64_t> F = {0, 0, 1};
    while(F.size() < 80)
        F.push_back(F.end()[-1] + F.end()[-2]);

    mt19937_64 gen(42);

    while(true)
    {
        int64_t x;
        //cin >> x;
        x = uniform_int_distribution<int64_t>{0, int64_t(5e7)}(gen);
        cout << x << endl;

        auto X = mod_zeckendorf(x, F);
        cout << "< ";
        for(int64_t f : X)
            cout << f << " ";
        cout << ">" << endl;

        auto Y = reway(x, F);
        cout << "< ";
        for(int64_t f : Y)
            cout << f << " ";
        cout << ">" << endl;

        auto Z = gamma(x, F);

        assert(accumulate(X.begin(), X.end(), 0) == x);
        assert(accumulate(Y.begin(), Y.end(), 0) == x);
        assert(Y.size() <= X.size());
        assert(Z <= Y.size());
    }

    /*
    const uint32_t Zits = 15;
    vector<vector<vector<int32_t>>> R(F[Zits]);
    for(uint32_t m = 0; m < power(3u, Zits); m++)
    {
        uint32_t n = m;
        vector<int32_t> c;
        for(uint32_t i = Zits; i --> 0;)
        {
            int32_t f = (int(n%3)-1) * F[i];
            if(f) c.push_back(f);
            n /= 3;
        }
        int32_t t = accumulate(c.begin(), c.end(), 0);
        if(0 <= t and t < (int32_t)R.size())
        {
            if(R[t].empty() or R[t][0].size() > c.size())
                R[t].clear();
            if(R[t].empty() or R[t][0].size() == c.size())
                R[t].push_back(c);
        }
    }

    for(uint32_t i = 0; i < F[Zits]; i++)
    {
        sort(R[i].begin(), R[i].end());
        R[i].erase(unique(R[i].begin(), R[i].end()), R[i].end());
        auto G = mod_zeckendorf(i, F);
        if(G.size() > R[i][0].size())
        {
            cout << i << ": ";
            for(auto v : R[i])
            {
                cout << "< ";
                for(int f : v)
                    cout << f << " ";
                cout << ">; ";
            }
            cout << " | ? ";
            cout << "< ";
            for(int f : G)
                cout << f << " ";
            cout << ">; ";
            cout << endl;
        }
    }
    */
}
