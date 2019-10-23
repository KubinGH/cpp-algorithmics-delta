#include <bits/stdc++.h>

using namespace std;

array<int, 2> diplus(const array<int, 2>& a, const array<int, 2>& b)
{
    return {min(a[0]+b[0], (1<<28)), min(a[1]+b[1], (1<<28))};
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    array<array<int, 2>, 2048> C;
    C[0] = {1<<28, 1<<28};
    C[1] = {0, 0};
    for(size_t i = 1; i < 2048; i++)
    {
        if(2*i < 2048) C[2*i] = {C[i][0] + 1, C[i][1]};
        if(5*i < 2048) C[5*i] = {C[i][0], C[i][1] + 1};
    }

    vector<vector<array<int, 2>>> A(n, vector<array<int, 2>>(m));

    bool zero = false;
    for(size_t i = 0; i < n; i++)
        for(size_t j = 0; j < m; j++)
    {
        int x;
        cin >> x;
        x = abs(x);
        A[i][j] = C[x];
        if(not x) zero = true;
    }

    int result = INT_MAX;
    for(size_t tt = 0; tt < 2; tt++)
    {
        vector<vector<array<int, 2>>> Q(n, vector<array<int, 2>>(m));

        Q[0][0] = A[0][0];
        for(size_t i = 1; i < n; i++)
            Q[i][0] = diplus(A[i][0], Q[i-1][0]);
        for(size_t i = 1; i < m; i++)
            Q[0][i] = diplus(A[0][i], Q[0][i-1]);
        for(size_t i = 1; i < n; i++)
          for(size_t j = 1; j < m; j++)
            Q[i][j] = diplus(A[i][j], min(Q[i-1][j], Q[i][j-1]));

        result = min(result, min(Q[n-1][m-1][0], Q[n-1][m-1][1]));

        for(auto& row : A)
            for(auto& col : row)
                swap(col[0], col[1]);
    }

    if(zero)
        result = min(result, 1);

    cout << result;
}
