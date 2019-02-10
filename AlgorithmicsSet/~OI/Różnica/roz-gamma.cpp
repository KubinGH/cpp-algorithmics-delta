#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n; string S;
    cin >> n;
    S.reserve(n);
    cin >> S;
    vector<uint32_t> O[32];
    for(uint32_t i = 0; i < S.size(); i++)
        O[S[i]-'a'].push_back(i);

    int32_t result = 0;
    vector<uint32_t> I; I.reserve(n);
    for(char master = 'a'; master <= 'z'; master++)
        for(char slave = 'a'; slave <= 'z'; slave++) if(master != slave)
    {
        I.clear();
        uint32_t c1 = master-'a', c2 = slave-'a';
        merge(O[c1].begin(), O[c1].end(), O[c2].begin(), O[c2].end(),
              back_inserter(I));
        int32_t p[2] = {0, -(int)n};
        for(uint32_t i : I)
        {
            p[0] = max(p[0], 0);
            if(S[i] == master)
                p[0]++, p[1]++;
            else
                p[1] = max(p[0], p[1]), p[0]--, p[1]--;
            result = max(result, p[1]);
        }
    }
    cout << result;
}
