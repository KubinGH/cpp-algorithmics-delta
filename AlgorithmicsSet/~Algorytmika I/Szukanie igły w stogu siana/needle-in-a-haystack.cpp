#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    string P, T;
    cin >> P >> T;
    auto S = P + '#' + T;

    vector<size_t> Pi(S.size());

    vector<size_t> occ;
    for(size_t i = 1, k = 0; i < S.size(); i++)
    {
        while(k and S[i] != S[k])
            k = Pi[k - 1];
        if(S[i] == S[k])
            k++;
        Pi[i] = k;

        if(i > P.size() and Pi[i] >= P.size())
            occ.push_back(i - 2*P.size() + 1);
    }

    cout << occ.size() << endl;
    for(auto i : occ)
        cout << i << ' ';
}
