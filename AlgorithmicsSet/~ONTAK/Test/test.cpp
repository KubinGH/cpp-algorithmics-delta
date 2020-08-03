#include <bits/stdc++.h>

using namespace std;

const size_t N = 2048;

bitset<N> ld()
{
    string S;
    cin >> S;
    bitset<N> A = {};
    for(size_t i = 0; i < S.size(); i++)
        A[i] = S[i] == '1';
    return A;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    vector<bitset<N>> B(n), Bs(n);
    bitset<N> all_n = {};
    for(size_t i = 0; i < n; i++)
    {
        all_n[i] = 1;
        for(size_t j = 0; j < n; j++)
        {
            char c;
            cin >> c;
            B[i][j] = (c == 'B');
            Bs[i][j] = (j ? Bs[i][j-1] : 0) ^ B[i][j];
        }
    }

    while(q --> 0)
    {
        auto curr = ld(), last = ld(), left = ld(), right = ld();

        bool ok = true;
        for(size_t i = 0; ok and i < n; i++)
        {
            auto L = Bs[i];
            if(left[i])
                L ^= all_n;
            ok &= (L[n-1] == right[i]);
            auto bnot = B[i] ^ all_n;
            ok &= ((bnot & (L ^ curr)) == bnot);
            curr ^= B[i];
        }
        cout << (ok and curr == last ? "YES" : "NO") << endl;
    }
}
