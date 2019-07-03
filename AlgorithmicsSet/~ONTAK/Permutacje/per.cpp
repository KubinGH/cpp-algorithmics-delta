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
        cout << "NO\n";
        continue;
    }

    mt19937_64 gen(42);
    vector<uint64_t> H(n);
    for(size_t i = 1; i < n; i++)
        H[i] = gen();
    vector<uint64_t> G(n + 1);
    partial_sum(H.begin(), H.end(), G.begin()+1, bit_xor<uint64_t>{});

    vector<uint64_t> P(n + 1);
    for(size_t i = 1; i <= n; i++)
        P[i] = P[i-1] ^ H[A[i-1]];

    vector<bool> C(n + 1);
    C[0] = true;
    for(size_t i = 1; i <= n; i++)
    {
        bool ok = false;
        for(size_t j = 0; j < i and not ok; j++)
            if(C[j] and (P[i]^P[j]) == G[i-j])
                ok = true;
        C[i] = ok;
    }
    cout << (C[n] ? "YES\n" : "NO\n");
  }
}