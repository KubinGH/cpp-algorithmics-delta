#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    vector<vector<uint32_t>> P(k, vector<uint32_t>(n));
    for(uint32_t i = 0; i < k; i++)
        for(uint32_t j = 0; j < n; j++)
            cin >> P[i][j], P[i][j]--;
    vector<uint32_t> K(k);
    iota(K.begin(), K.end(), 0);
    uint32_t result = 0;
    do {
        vector<uint32_t> A(n), B(n);
        iota(B.begin(), B.end(), 0);
        for(uint32_t i : K)
        {
            A.swap(B);
            for(uint32_t j = 0; j < n; j++)
                B[j] = A[P[i][j]];
        }
        for(uint32_t j = 0; j < n; j++)
            if(B[j] == j)
                result++;
    } while(next_permutation(K.begin(), K.end()));
    cout << result;
}
