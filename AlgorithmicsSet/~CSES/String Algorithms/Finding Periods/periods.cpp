#include <bits/stdc++.h>

using namespace std;

template<typename It>
vector<size_t> prefixosuffixes(It first, It last)
{
    using T = typename It::value_type;
    static vector<T> S;
    S.clear(); copy(first, last, back_inserter(S));
    vector<size_t> P(S.size());
    for(size_t i = 1; i < S.size(); i++)
    {
        P[i] = P[i - 1];
        while(P[i] and S[i] != S[P[i]])
            P[i] = P[P[i] - 1];
        if(S[i] == S[P[i]])
            P[i]++;
    }
    return P;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string S;
    cin >> S;
    auto P = prefixosuffixes(S.begin(), S.end());
    size_t p = P[S.size() - 1];
    vector<size_t> R;
    while(p)
        R.push_back(S.size() - p), p = P[p - 1];
    R.push_back(S.size());
    for(auto r : R)
        cout << r << ' ';
    cout << endl;
}
