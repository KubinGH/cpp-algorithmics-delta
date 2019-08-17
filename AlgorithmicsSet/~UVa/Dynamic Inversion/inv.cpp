#include <bits/stdc++.h>
#include <ktl/structures/fenwick.cpp>

using namespace std;

int main()
{
  ios::sync_with_stdio(false); cin.tie(nullptr);

  size_t n, m;
  while(cin >> n >> m)
  {

    vector<size_t> A(n), B(n);
    for(size_t i = 0; i < n; i++)
    {
        cin >> A[i], A[i]--;
        B[A[i]] = i;
    }

    const size_t k = ceil(sqrt(n)), b = (n + k - 1) / k;


    vector<vector<size_t>> blocks(b), ord_blocks(b);
    for(size_t p = 0; p < n; p += k)
    {
        size_t e = p / k;
        size_t q = min(p+k, n);

        for(size_t i = p; i < q; i++)
            blocks[e].push_back(A[i]);

        ord_blocks[e] = blocks[e];
        sort(ord_blocks[e].begin(), ord_blocks[e].end());
    }

    uint64_t inversions = 0;
    fenwick_tree<uint64_t> F(n + 1);
    for(size_t i = 0; i < n; i++)
    {
        inversions += F.get(A[i] + 1, n);
        F.delta(A[i], 1);
    }

    while(m --> 0)
    {
        size_t x;
        cin >> x; x--;

        cout << inversions << '\n';

        size_t e = B[x] / k;

        auto it  = find(blocks[e].begin(), blocks[e].end(), x);
        auto ito = find(ord_blocks[e].begin(), ord_blocks[e].end(), x);

        auto ix = size_t(it - blocks[e].begin());
        for(size_t i = 0; i < ix; i++)
            if(blocks[e][i] > x)
                inversions--;
        for(size_t i = ix+1; i < blocks[e].size(); i++)
            if(blocks[e][i] < x)
                inversions--;

        for(size_t f = 0; f < e; f++)
        {
            auto that = upper_bound(ord_blocks[f].begin(), ord_blocks[f].end(), x);
            inversions -= blocks[f].size() - (that - ord_blocks[f].begin());
        }
        for(size_t f = e+1; f < b; f++)
        {
            auto that = upper_bound(ord_blocks[f].begin(), ord_blocks[f].end(), x);
            inversions -= that - ord_blocks[f].begin();
        }

        blocks[e].erase(it);
        ord_blocks[e].erase(ito);
    }

  }
}
