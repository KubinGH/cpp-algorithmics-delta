// this is O(n+m+q log k) instead of O(m+nq) like the model solution
// why?

#include <functional>
#include <cstdint>
#include <cassert>
#include <climits>
#include <vector>
#include <array>

using namespace std;

const size_t nil = SIZE_MAX;

void answer(int);


void count_routes(int _n, int _m, int _t, int E[][2], int _q, int K[])
{
    const size_t n = _n, m = _m, target = _t, q = _q;

    // get edges
    vector<array<size_t, 2>> to(n, {nil, nil});
    for(size_t i = 0; i < m; i++)
    {
        size_t u = E[i][0], v = E[i][1];
        if(to[u][0] == nil)
            to[u][0] = v;
        else if(to[u][1] == nil)
            to[u][1] = v;
        if(to[v][0] == nil)
            to[v][0] = u;
        else if(to[v][1] == nil)
            to[v][1] = u;
    }

    vector<size_t> F(2*n, nil);
    // vertex i+n is vertex after coming through best edge of vertex i
    auto nfix = [&](size_t v, size_t u) {
        return v + (to[v][0] == u ? n : 0);
    };
    for(size_t u = 0; u < n; u++)
    {
        F[u] = nfix(to[u][0], u);
        F[u+n] = nfix(to[u][1] == nil ? to[u][0] : to[u][1], u);
    }

    // rho computation
    vector<bool> vis(2*n), on(2*n);
    vector<size_t> st; st.reserve(2*n);

    vector<size_t> top(2*n, nil);
    vector<int> lambda(2*n), omega(2*n);

    vector<vector<size_t>> G(2*n);

    for(size_t s = 0; s < 2*n; s++)
    {
        G[F[s]].push_back(s);
        // cout << s << " " << F[s] << endl;
        if(vis[s])
            continue;

        assert(st.empty());
        size_t u = s;
        while(true)
        {
            vis[u] = on[u] = true;
            st.push_back(u);

            if(on[F[u]])
            {
                vector<size_t> cycle;
                while(true)
                {
                    auto v = st.back(); st.pop_back();
                    on[v] = false;
                    cycle.push_back(v);
                    if(v == F[u])
                        break;
                }
                for(auto v : cycle)
                    omega[v] = cycle.size(), top[v] = v;
            }
            else if(vis[F[u]])
            {
                lambda[u] = lambda[F[u]] + 1;
                top[u] = top[F[u]];
            }
            else
                { u = F[u]; continue; }
            break;
        }
        while(not st.empty())
        {
            auto v = st.back(); st.pop_back();
            lambda[v] = lambda[F[v]] + 1;
            top[v] = top[F[v]];
            on[v] = false;
        }
    }


    // queries

    vector<pair<vector<int>, int>> tabs(2*n);
    function<pair<vector<int>, int>(size_t)> get_tab = [&](size_t t) -> pair<vector<int>, int> {
        if(not tabs[t].first.empty())
            return tabs[t];
        else if(lambda[t])
        {
            vector<int> cnt;
            function<void(size_t, size_t)> dfs = [&](size_t u, size_t d) {
                while(cnt.size() <= d) cnt.push_back(0);
                cnt[d] += (u < n);
                for(auto v : G[u])
                    dfs(v, d + 1);
            };
            dfs(t, 0);
            return tabs[t] = {cnt, 0};
        }
        else
        {
            size_t u = t;
            vector<int> cnt(omega[t]);
            for(int i = 0; i < omega[t]; i++, u = F[u])
            {
                int sh = (i ? omega[t] - i : 0);
                cnt[sh] += (u < n);
                sh++;
                for(auto v : G[u])
                  if(lambda[v])
                {
                    auto [sub, _] = get_tab(v);
                    (void)_;
                    while(cnt.size() < sh + sub.size()) cnt.push_back(0);
                    for(size_t d = 0; d < sub.size(); d++)
                        cnt[sh + d] += sub[d];
                }
            }
            for(size_t i = omega[t]; i < cnt.size(); i++)
                cnt[i] += cnt[i - omega[t]];
            return tabs[t] = {cnt, omega[t]};
        }
    };

    auto count = [&](int k, size_t t) {
        auto [T, mod] = get_tab(t);
        if(mod)
        {
            int step = mod;
            while(2*step < INT_MAX/5)
                step *= 2;
            while(step > mod)
            {
                while(k >= (int)T.size()+step)
                    k -= step;
                step /= 2;
            }
            while((size_t)k >= T.size())
                k -= mod;
            return T[k];
        }
        else
            return (size_t)k < T.size() ? T[k] : 0;
    };

    for(size_t que = 0; que < q; que++)
    {
        int k = K[que];
        answer(count(k, target) + count(k, target + n));
    }
}
