#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m; int k;
    cin >> n >> m >> k;

    map<int, int> remap;

    vector<int> A(n), B(m);
    for(auto& a : A) cin >> a, remap[a];
    for(auto& b : B) cin >> b, remap[b];

    size_t f = 0;
    for(auto& kv : remap)
        kv.second = f++;
    vector<int> demap(f);
    for(auto& kv : remap)
        demap[kv.second] = kv.first;

    for(auto& a : A) a = remap[a];
    for(auto& b : B) b = remap[b];

    vector<int> curr(m+1, INT_MIN), fwd = curr;
    curr[0] = 0;
    vector<size_t> last(f);

    for(size_t i = 0; i < n; i++)
    {
        copy(curr.begin(), curr.end(), fwd.begin());
        fill(last.begin(), last.end(), m);
        for(size_t j = m; j --> 0; )
        {
            last[B[j]] = j;
            if(not j or __builtin_popcount(demap[A[i]] ^ demap[B[j-1]]) <= k)
            {
                auto j1 = last[A[i]];
                if(j1 < m)
                    fwd[j1 + 1] = max(fwd[j1 + 1], curr[j] + 1);
            }
        }
        swap(curr, fwd);
    }

    cout << *max_element(curr.begin(), curr.end()) << endl;
}
