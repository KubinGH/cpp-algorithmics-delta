#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    string S;
    cin >> S;

    vector<size_t> P(S.size());

    cout << "0 ";
    for(size_t i = 1, k = 0; i < S.size(); i++)
    {
        while(k and S[i] != S[k])
            k = P[k - 1];
        if(S[i] == S[k])
            k++;
        P[i] = k;

        cout << P[i] << ' ';
    }

    cout << endl;
}
