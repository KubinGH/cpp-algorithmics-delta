#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, k;
    cin >> n >> k;

    vector<int> M(k);
    for(auto& m : M)
        cin >> m;

    vector<bool> W(n + 1);

    for(int i = 1; i <= (int)n; i++)
    {
        for(auto j : M)
            if(i >= j)
                W[i] = W[i] or not W[i - j];
        cout << (W[i] ? 'W' : 'L');
    }
    cout << endl;
}
