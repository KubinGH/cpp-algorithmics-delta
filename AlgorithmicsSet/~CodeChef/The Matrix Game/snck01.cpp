#include <bits/stdc++.h>

using namespace std;

size_t nimber_of_row(const vector<size_t>& A)
{
    const size_t n = A.size(), m = *max_element(A.begin(), A.end());
    vector<vector<size_t>> F(n, vector<size_t>(m+1));
    F[n-1][A[n-1]] = A[n-1];

    for(size_t i = n-1; i --> 0; )
    {
        vector<bool> S(m+2);
        S[F[i][0] = F[i+1][A[i+1]]] = true;
        size_t mex = 0;
        for(size_t a = 1; a <= A[i]; a++)
        {
            while(S[mex])
                mex++;
            S[F[i][a] = mex] = true;
        }
    }

    return F[0][A[0]];
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t t;
    cin >> t;
    while(t --> 0)
    {
        size_t h, w;
        cin >> h >> w;

        vector<vector<size_t>> M(h, vector<size_t>(w));
        for(size_t y = 0; y < h; y++)
            for(size_t x = 0; x < w; x++)
                cin >> M[y][x];

        size_t nimber = 0;
        for(size_t y = 0; y < h; y++)
            nimber ^= nimber_of_row(M[y]);

        cout << (nimber ? "FIRST" : "SECOND") << '\n';
     }
}
