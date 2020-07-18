#include <bits/stdc++.h>

using namespace std;

enum Protocol
{
    IAmYourFriend = 0,
    MyFriendsAreYourFriends = 1,
    WeAreYourFriends = 2
};

int findSample(int _n, int val[], int host[], int protocol[])
{
    size_t n = _n;

    vector<vector<size_t>> graph(n);
    auto conn = [&](size_t u, size_t v) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    };

    uint mask = 0;
    bool units = val[0] == 1;
    for(size_t i = 1; i < n; i++)
    {
        mask |= 1<<protocol[i];
        units &= val[i] == 1;
        if(protocol[i] == IAmYourFriend)
            conn(i, host[i]);
        else if(protocol[i] == MyFriendsAreYourFriends)
            for(auto u : graph[host[i]])
                conn(i, u);
        else if(protocol[i] == WeAreYourFriends)
        {
            for(auto u : graph[host[i]])
                conn(i, u);
            conn(i, host[i]);
        }
    }

    if(not mask or mask == (1<<MyFriendsAreYourFriends))
        return accumulate(val, val + n, 0);
    else if(mask == (1<<WeAreYourFriends))
        return *max_element(val, val + n);
    else if(mask == (1<<IAmYourFriend))
    {
        vector<array<int, 2>> Q(n);
        for(size_t u = n; u --> 0; )
        {
            Q[u] = {0, val[u]};
            for(auto v : graph[u]) if(u == 0 or (int)v != host[u])
            {
                Q[u][0] += max(Q[v][0], Q[v][1]);
                Q[u][1] += Q[v][0];
            }
        }
        return max(Q[0][0], Q[0][1]);
    }
    else if(mask == ((1<<IAmYourFriend) | (1<<MyFriendsAreYourFriends)) and units)
    {
        vector<bool> vis(n);
        vector<size_t> match(n, SIZE_MAX);

        function<bool(size_t)> augment = [&](size_t u) {
            vis[u] = true;
            for(auto v : graph[u])
                if(match[v] == SIZE_MAX)
                    { match[u] = v; match[v] = u; return true; }
            for(auto v : graph[u])
                if(not vis[match[v]] and augment(match[v]))
                    { match[u] = v; match[v] = u; return true; }
            return false;
        };
        size_t result = 0;
        while(true)
        {
            fill(vis.begin(), vis.end(), false);
            bool any = false;
            for(size_t u = 0; u < n; u++)
                if(match[u] == SIZE_MAX and augment(u))
                    any = true, result++;
            if(not any) break;
        }
        return n - result;
    }
    else
    {
        int result = 0;
        for(size_t s = 0; s < (1u << n); s++)
        {
            int curr = 0;
            bool ok = true;
            for(size_t i = 0; i < n; i++) if(s & (1 << i))
            {
                curr += val[i];
                for(size_t j = 0; j < n; j++) if(s & (1 << j))
                    if(find(graph[i].begin(), graph[i].end(), j) != graph[i].end())
                        ok = false;
            }
            if(ok)
                result = max(result, curr);
        }
        return result;
    }
}
