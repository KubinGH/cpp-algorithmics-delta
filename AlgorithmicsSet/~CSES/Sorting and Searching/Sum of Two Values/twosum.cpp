#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n; int x;
    cin >> n >> x;

    unordered_map<int, size_t> where;
    where.reserve(4 * n);
    bool found = false;
    for(size_t i = 1; i <= n; i++)
    {
        int a;
        cin >> a;
        if(where[x - a])
        {
            cout << where[x - a] << ' ' << i << endl;
            found = true;
            break;
        }
        where[a] = i;
    }
    if(not found)
        cout << "IMPOSSIBLE" << endl;
}
