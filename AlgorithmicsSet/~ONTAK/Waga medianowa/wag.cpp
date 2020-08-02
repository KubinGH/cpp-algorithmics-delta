#include <bits/stdc++.h>

using namespace std;

int init();
int median(int, int, int);
void answer(int);

struct ret_t
{
    array<pair<int, int>, 2> sol;
    array<vector<int>, 3> stat;
};

ret_t find_indices(int u, int v, int L, int R, vector<int> pos)
{
    array<vector<int>, 3> ret = {};
    for(int p : pos)
    {
        auto r = median(u, v, p);
        ret[r == u ? 0 : (r == v ? 1 : 2)].push_back(p);
    }

    int A = ret[0].size(), B = ret[1].size(), C = ret[2].size() + 1;
    if(A > B) swap(A, B);

    array<pair<int, int>, 2> result; size_t ri = 0;
    for(int i = L; i+C <= R; i++)
    {
        int j = i + C;
        auto a = i-L, b = R-j;
        if(a > b) swap(a, b);
        if(a == A and b == B)
        {
            auto ii = i, jj = j;
            if(ii-L == (int)ret[1].size()) swap(ii, jj);
            result[ri++] = {ii, jj};
            if(ii-L == R-jj)
                result[ri++] = {jj, ii};
        }
    }

    return ret_t {result, ret};
}

template<typename T>
void discard(vector<int>& v, T x)
{
    auto it = find(v.begin(), v.end(), x);
    if(it != v.end())
        v.erase(it);
}

int main()
{
    mt19937 g(1337);
    int n = init();

    if(n == 1) { answer(0); return 0; }

    int L = 0, R = n-1;
    vector<int> pos(n);
    iota(pos.begin(), pos.end(), 0);
    int u = uniform_int_distribution<int>{0, n-1}(g);
    int v = uniform_int_distribution<int>{0, n-2}(g);
    if(v >= u) v++;
    auto pick_pivot = [&]() {
        return pos[uniform_int_distribution<size_t>{0, pos.size() - 1}(g)];
    };


    int ui = -1, vi = -1;
    while(true)
    {
        discard(pos, u);
        discard(pos, v);
        auto ret = find_indices(u, v, L, R, pos);
        int s;
        if(ui != -1)
            s = ret.sol[1].first == ui;
        else if(vi != -1)
            s = ret.sol[1].second == vi;
        else
            s = 0;

        auto [i, j] = ret.sol[s];
        if(i > j) swap(i, j), swap(u, v), swap(ret.stat[0], ret.stat[1]);

        if(i == n/2) { answer(u); break; }
        else if(j == n/2) { answer(v); break; }
        else if(n/2 < i)
        {
            R = i;
            v = u;
            ui = -1; vi = i;
            pos = ret.stat[0];
            u = pick_pivot();
        }
        else if(j < n/2)
        {
            L = j;
            u = v;
            ui = j; vi = -1;
            pos = ret.stat[1];
            v = pick_pivot();
        }
        else
        {
            L = i; R = j-1;
            ui = i; vi = -1;
            pos = ret.stat[2];
            v = pick_pivot();
        }
    }
}
