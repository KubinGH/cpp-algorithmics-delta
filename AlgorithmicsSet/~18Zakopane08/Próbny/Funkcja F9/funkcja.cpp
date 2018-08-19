#include <bits/stdc++.h>

using namespace std;

const uint32_t A[] = {
    2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5,
    6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<string> V;
    for(uint32_t i = 0; i < n; i++)
    {s
        string c;
        cin >> c;
        V.push_back(c);
    }
    string K;
    cin >> K;
    uint32_t r = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        bool ok = true;
        for(uint32_t j = 0; j < V[i].size() and ok; j++)
            if(A[size_t(V[i][j]-'a')] != uint32_t(K[j]-'0'))
                ok = false;
        if(ok)
            r++;
    }
    cout << r;
}
