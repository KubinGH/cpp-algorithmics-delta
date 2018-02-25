#include <bits/stdc++.h>

using namespace std;

typedef pair<uint32_t, uint32_t> pair_u32;

vector<int> find_subset(int al, int au, vector<int> w)
{
    uint32_t l = al, u = au;
    vector<int> result;
    vector<pair<uint64_t, uint32_t>> W;
    for(uint32_t i = 0; i < w.size(); i++)
        W.emplace_back(w[i], i);
    sort(W.begin(), W.end());
    vector<uint64_t> S; S.push_back(0);
    for(uint32_t i = 1; i < W.size()+1; i++)
        S.emplace_back(W[i-1].first + S[i-1]);
    for(uint32_t i = 0; i < W.size(); i++)
    {
        uint32_t j = distance(S.begin(), upper_bound(S.begin()+i, S.end(), S[i]+l-1));
        if(S[j] - S[i] > u)
            j--;
        if(S[j] - S[i] >= l and S[j] - S[i] <= u)
        {
            for(uint32_t k = i; k < j; k++)
                result.push_back(W[k].second);
            return result;
        }
    }
    return result;
}

/*
int main()
{
    uint32_t n, l, u;
    cin >> n >> l >> u;
    vector<int> w;
    for(uint32_t i = 0; i < n; i++)
    {
        int c;
        cin >> c;
        w.push_back(c);
    }
    for(uint32_t x : solve(l, u, w))
        cout << x << " ";
}
*/
