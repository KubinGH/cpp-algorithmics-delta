#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m; uint p;
    cin >> n >> m >> p;

    vector<vector<uint>> A(m, vector<uint>(m, 1));
    for(size_t t = 1; t < n; t++)
    {
        vector<vector<uint>> B(m, vector<uint>(m));
        for(size_t i = 0; i < m; i++)
            for(size_t j = i; j < m; j++)
                for(size_t k = 0; k < m; k++)
                    for(size_t l = k; l < m; l++)
                        if(not (j < k or l < i))
                            B[k][l] += A[i][j], B[k][l] %= p;
        swap(A, B);
    }

    uint result = 0;
    for(size_t i = 0; i < m; i++)
        for(size_t j = i; j < m; j++)
            result += A[i][j], result %= p;

    cout << result << endl;
}
