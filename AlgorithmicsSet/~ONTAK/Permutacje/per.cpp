#include <bits/stdc++.h>

using namespace std;

int main()
{
  ios::sync_with_stdio(false); cin.tie(nullptr);
  size_t z;
  cin >> z;
  while(z --> 0)
  {
    size_t n;
    cin >> n;

    vector<size_t> A(n);
    bool fail = false;
    for(size_t i = 0; i < n; i++)
    {
        cin >> A[i];
        A[i]--;
        if(A[i] >= n)
            fail = true;
    }
    if(fail)
    {
        cout << "NO" << endl;
        continue;
    }

    mt19937 gen(42);
    vector<unsigned> H(n);
    for(size_t i = 1; i < n; i++)
        H[i] = gen();
    vector<unsigned> G(n + 1);
    partial_sum(H.begin(), H.end(), G.begin()+1, bit_xor<unsigned>{});

    auto righty_edges = [&]() {
        vector<unsigned> P(n + 1);
        for(size_t i = 1; i <= n; i++)
            P[i] = P[i-1] ^ H[A[i-1]];

        auto is_ok = [&](size_t l, size_t r) {
            return (P[l] ^ P[r]) == G[r - l];
        };

        vector<pair<size_t, size_t>> E;

        vector<size_t> zeroes;
        for(size_t i = 0; i < n; i++)
            if(A[i] == 0)
                zeroes.push_back(i);
        if(zeroes.empty())
            return E;

        vector<pair<size_t, size_t>> intervals;
        for(size_t i = 0; i+1 < zeroes.size(); i++)
            intervals.emplace_back(zeroes[i], zeroes[i+1]);
        intervals.emplace_back(zeroes.back(), n);

        for(auto it : intervals)
        {
            size_t o = it.first, stop = it.second;
            for(size_t i = o, mx = 0; i < stop; i++)
            {
                mx = max(A[i], mx);
                if(i < mx) continue;
                if(is_ok(i - mx, i + 1))
                    E.emplace_back(i - mx, i + 1);
            }
        }

        return E;
    };

    auto E = righty_edges();
    reverse(A.begin(), A.end());
    auto E1 = righty_edges();
    reverse(A.begin(), A.end());
    for(auto p : E1)
        E.emplace_back(n - p.second, n - p.first);

    vector<bool> V(n + 1);
    V[0] = true;
    sort(E.begin(), E.end());
    for(auto e : E)
        if(V[e.first])
            V[e.second] = true;

    cout << (V[n] ? "YES" : "NO") << endl;
  }
}
