#include <bits/stdc++.h>

using namespace std;

int main()
{
    size_t n, x;
    cin >> n >> x;

    vector<size_t> W(n);
    vector<int> V(n), P(x+1);
    for(auto& w : W) cin >> w;
    for(auto& v : V) cin >> v;

    for(size_t i = 0; i < n; i++)
        for(size_t a = x+1; a --> W[i]; )
            P[a] = max(P[a], P[a-W[i]] + V[i]);

    cout << P[x] << endl;
}
