#include <bits/stdc++.h>

using namespace std;

const uint32_t MOD = 1e9 + 7;

int main()
{
    uint32_t n;
    cin >> n;
    vector<uint32_t> A(n+1), B(n+1);
    vector<uint32_t> marks; marks.reserve(2*n + 1);
    for(uint32_t i = 1; i <= n; i++)
    {
        cin >> A[i] >> B[i];
        marks.push_back(A[i]); marks.push_back(B[i]);
    }
    marks.push_back(0);
    sort(marks.begin(), marks.end());
    marks.erase(unique(marks.begin(), marks.end()), marks.end());

    vector<map<uint32_t, uint32_t>> Q(n+1), E(n+1), QQ(n+1);
    for(uint32_t x = 0; x <= marks.back(); x++)
        Q[0][x] = 1, QQ[0][x] = x + 1;
    E[0][0] = 1;

    uint32_t result = 0;
    for(uint32_t i = 1; i <= n; i++)
    {
        uint32_t a = A[i], b = B[i];
        for(uint32_t xi = 1; xi < marks.size(); xi++)
        {
            uint32_t x = marks[xi], x1 = marks[xi-1];
            Q[i][x] = Q[i][x1];
            QQ[i][x-1] = QQ[i][x1] + Q[i][x1] * (x - x1);
            for(uint32_t j = 0; j < i; j++)
            {
                Q[i][x] += (MOD + QQ[j][x] - QQ[j][x1]) % MOD;
                E[i][x] += (MOD + Q[j][x] - E[j][x]) % MOD;
                Q[i][x] %= MOD;
            }
        }
        result += Q[i][b];
        result %= MOD;
    }

    cout << result;
}
