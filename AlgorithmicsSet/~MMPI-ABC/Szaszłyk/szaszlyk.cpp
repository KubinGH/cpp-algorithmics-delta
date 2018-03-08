#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    string S; S.reserve(n);
    cin >> S;
    vector<pair<char, uint32_t>> V; V.reserve(n);
    V.emplace_back(S[0], 1);
    uint32_t result = 0;
    for(uint32_t i = 1; i < n; i++)
    {
        if(S[i] == V.back().first)
            V.back().second++;
        else
            V.emplace_back(S[i], 1);
        if(V.back().second == 2)
        {
            result += 2;
            V.pop_back();
        }
    }
    cout << result;
}
