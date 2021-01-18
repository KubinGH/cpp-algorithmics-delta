#include <bits/stdc++.h>

using namespace std;

pair<string, string> evenodd(string S)
{
    string S0, S1;
    for(size_t i = 0; i < S.size(); i++)
        (i % 2 ? S0 : S1).push_back(S[i]);

    return {S0, S1};
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    string S, T;
    cin >> S >> T;
    auto [S0, S1] = evenodd(S);
    auto [T0, T1] = evenodd(T);

    sort(S0.begin(), S0.end());
    sort(S1.begin(), S1.end());
    sort(T0.begin(), T0.end());
    sort(T1.begin(), T1.end());

    cout << (S0 == T0 and S1 == T1 ? "TAK" : "NIE") << endl;

}
