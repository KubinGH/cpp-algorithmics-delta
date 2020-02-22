#include <bits/stdc++.h>
#ifdef XHOVA
#define cdbg cerr
#else
#define cdbg if(0) cerr
#endif

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<int> P(n);
    for(auto& p : P)
        cin >> p;

    vector<vector<pair<size_t, int>>> graph(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v; int b;
        cin >> u >> v >> b; u--; v--;
        graph[u].emplace_back(v, b);
        graph[v].emplace_back(u, b);
    }

    auto fail = []() {
        cout << "NIE" << endl;
        exit(0);
    };

    vector<int> A(n);
    vector<int64_t> D(n);

    vector<bool> vis(n);

    int64_t r_min = 0, r_max = 0;
    for(size_t s = 0; s < n; s++)
    {
        if(vis[s])
            continue;

        vis[s] = true;
        vector<size_t> S = {s};

        A[s] = 1; D[s] = 0;

        bool force = false; int force_x;

        cdbg << "s = " << s+1 << endl;

        for(size_t i = 0; i < S.size(); i++)
        {
            const auto u = S[i];

            for(auto [v, b] : graph[u])
            {
                if(not vis[v])
                {
                    A[v] = -A[u];
                    D[v] = P[u] + P[v] - b - D[u];
                    vis[v] = true;
                    S.push_back(v);
                }
                else
                {
                    auto val = P[u] + P[v] - D[u] - D[v] - b;
                    if(A[u] + A[v] == 0)
                    {
                        if(val != 0)
                            fail();
                    }
                    else
                    {
                        if(val % (A[u] + A[v]) == 0)
                        {
                            auto f = val / (A[u] + A[v]);
                            if(not force or f == force_x)
                                force = true, force_x = f;
                            else
                                fail();
                        }
                        else
                            fail();
                    }
                }
            }
        }

        int64_t x_lo = 0, x_hi = P[s];
        int64_t a = 0, b = 0;
        for(auto u : S)
        {
            cdbg << u+1 << ": " << A[u] << "x + " << D[u] << " in [" << 0 << ", " << P[u] << "]" << endl;

            int64_t lo = -D[u], hi = P[u] - D[u];
            if(A[u] == -1)
                tie(lo, hi) = make_pair(-hi, -lo);
            x_lo = max(x_lo, lo);
            x_hi = min(x_hi, hi);

            a += A[u];
            b += D[u];
        }

        cdbg << x_lo << " <= x <= " << x_hi << endl;
        cdbg << " minimize f(x) = " << a << "x + " << b << endl;
        if(force)
            cdbg << " forcing x := " << force_x << endl;
        else
            cdbg << " NOT forcing x" << endl;

        if(x_lo > x_hi)
            fail();
        if(force)
        {
            if(not (x_lo <= force_x and force_x <= x_hi))
                fail();
            x_lo = x_hi = force_x;
        }

        auto [y_min, y_max] = minmax({a*x_lo + b, a*x_hi + b});
        r_min += y_min;
        r_max += y_max;
    }

    cout << r_min << ' ' << r_max << endl;
}
