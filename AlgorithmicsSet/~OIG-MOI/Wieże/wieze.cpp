#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    set<string> S;
    uint32_t r = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        string current;
        cin >> current;
        set<string>::iterator it;
        while((it = S.find(current)) != S.end())
        {
            S.erase(it);
            current.append(current);
        }
        S.insert(current);
        r = max(r, current.size());
    }
    cout << r;
}
