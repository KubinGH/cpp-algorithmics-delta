#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    string in;
    cin >> n >> q >> in;

    vector<int> S(n + 1);
    for(size_t i = 0; i < n; i++)
        S[i+1] = S[i] + (in[i] == 'D');

    vector<int> cnt(S.back() + 1);
    for(size_t i = 0; i <= n; i++)
        cnt[S[i]]++;

    while(q --> 0)
    {
        size_t d;
        cin >> d;
        int64_t result = 0;
        if(d) for(size_t s = 0; s + d < cnt.size(); s++)
            result += (int64_t) cnt[s + d] * cnt[s];
        else for(size_t s = 0; s < cnt.size(); s++)
            result += (int64_t) cnt[s] * (cnt[s] - 1) / 2; 
        cout << result << endl;
    }
}
