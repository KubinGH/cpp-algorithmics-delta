#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    while(m --> 0)
    {
        size_t u, v;
        cin >> u >> v;
        if(u > v)
            swap(u, v);
        cout << u << ' ' << v << '\n';
    }
}
