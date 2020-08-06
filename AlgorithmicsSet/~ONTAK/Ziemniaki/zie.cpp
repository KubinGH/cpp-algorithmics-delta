#include <bits/stdc++.h>

using namespace std;

size_t n;
set<array<size_t, 17>> vis;
void dfs(array<size_t, 17> p)
{
    if(vis.count(p))
        return;
    vis.insert(p);
    for(size_t i = 1; i <= n; i++)
      if(not p[i])
    {
        auto q = p;
        for(size_t j = 1; j <= n; j++)
        {
            if(p[j] == i)
                q[j] = 0;
            else if(i != j and p[j] == 0)
                q[j] = i;
        }
        dfs(q);
    }
}

int main()
{
    cin >> n;
    array<size_t, 17> p;
    for(size_t i = 1; i <= n; i++)
        cin >> p[i];
    dfs(p);
    cout << vis.size() << endl;
}
