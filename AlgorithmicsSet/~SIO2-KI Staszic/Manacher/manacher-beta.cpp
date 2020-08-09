#include <bits/stdc++.h>

using namespace std;

vector<size_t> manacher_odd(string S, char leafL = '$', char leafR = '^')
{
    const size_t n = S.size();
    S = leafL + S + leafR;

    vector<size_t> R(n+2);
    for(size_t i = 1, j = 0, r = 0; i <= n; i++)
    {
        if(i < r)
            R[i] = min(r - i, R[2*j - i]);
        while(S[i-R[i]] == S[i+R[i]])
            R[i]++;
        if(i+R[i] > r)
            j = i, r = i+R[i];
    }
    R.erase(R.begin()); R.pop_back();
    return R;
}

vector<size_t> manacher(string S, char leaf = '|')
{
    const size_t n = S.size();

    string Z(2*n + 1, leaf);
    for(size_t i = 0; i < n; i++)
        Z[2*i+1] = S[i];

    auto R = manacher_odd(Z);
    R.erase(R.begin()); R.pop_back();
    for(size_t i = 0; i < 2*n - 1; i++)
        R[i] /= 2;
    return R;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;
    string S;
    cin >> S;

    auto R = manacher(S);

    for(size_t i = 0; i < n; i++)
        cout << R[2*i] << ' ';
    cout << endl;
    for(size_t i = 0; i < n - 1; i++)
        cout << R[2*i+1] << ' ';
    cout << endl;
}
