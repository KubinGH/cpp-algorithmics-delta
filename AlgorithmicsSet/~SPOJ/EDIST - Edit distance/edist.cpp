#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t q;
    cin >> q;
    while(q --> 0)
    {
        string A, B;
        cin >> A >> B;
        vector<vector<uint32_t>> E(A.size()+1, vector<uint32_t>(B.size(), -1u));
        E[0][0] = 0;
        for(uint32_t i = 1; i <= A.size(); i++)
            E[i][0] = E[0][i] = i;
        for(uint32_t i = 0; i < A.size(); i++)
          for(uint32_t j = 0; j < B.size(); j++)
            E[i+1][j+1] = min({E[i][j] + (A[i] != B[j]), E[i][j+1] + 1, E[i+1][j] + 1});
        cout << E[A.size()][B.size()] << "\n";
    }
}
