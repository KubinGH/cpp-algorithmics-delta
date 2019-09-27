#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int W;
    cin >> W;

    size_t n;
    cin >> n;

    multiset<int> S;
    for(size_t i = 0; i < n; i++)
    {
        int w;
        cin >> w;
        S.insert(w);
    }

    size_t result = 0;
    while(not S.empty())
    {
        int a = *S.begin();
        S.erase(S.begin());

        if(not S.empty() and *S.begin() <= W - a)
        {
            auto it = S.upper_bound(W - a);
            --it;
            S.erase(it);
        }

        result++;
    }
    cout << result;
}
