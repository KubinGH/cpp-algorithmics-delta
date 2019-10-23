
#include <bits/stdc++.h>

using namespace std;

int main()
{
    size_t n, m;
    cin >> n >> m;
    vector<vector<unsigned>> K(n+1, vector<unsigned>(m+1));
    vector<vector<bool>> B(n+1, vector<bool>(m+1));
    vector<size_t> W(n);
    vector<unsigned> V(n);

    for(size_t i = 0; i < n; i++)
        cin >> W[i];
    for(size_t i = 0; i < n; i++)
        cin >> V[i];

    for(size_t i = 1; i <= n; i++)
        for(size_t w = 0; w <= m; w++)
    {
        K[i][w] = K[i-1][w];
        if(w >= W[i-1])
        {
            auto t = K[i-1][w-W[i-1]] + V[i-1];
            if(t > K[i][w])
                K[i][w] = t, B[i][w] = true;
        }
    }

    cout << K[n][m] << endl;

    stack<size_t> used;
    for(size_t i = n+1, w = m; i --> 0; )
    {
        if(B[i][w])
            w -= W[i-1], used.push(i);
    }

    cout << used.size() << endl;

    while(not used.empty())
        cout << used.top() << " ", used.pop();
    cout << endl;
}
