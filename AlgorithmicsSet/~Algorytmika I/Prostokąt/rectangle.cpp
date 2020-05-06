#include <bits/stdc++.h>

using namespace std;

int64_t kadane(const vector<int64_t>& A)
{
    int64_t best = 0, best_here = 0;
    for(auto a : A)
        best = max(best, best_here = max(best_here + a, (int64_t)0));
    return best;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<int64_t>> A(n, vector<int64_t>(m));
    for(auto& row : A)
        for(auto& a : row)
            cin >> a;

    if(n > m)
    {
        vector<vector<int64_t>> B(m, vector<int64_t>(n));
        for(size_t y = 0; y < m; y++)
            for(size_t x = 0; x < n; x++)
                B[y][x] = A[x][y];
        A.swap(B);
        swap(n, m);
    }

    int64_t result = 0;
    for(size_t i = 1; i <= n; i++)
    {
        vector<int64_t> C(m);
        for(size_t j = i; j --> 0; )
        {
            for(size_t k = 0; k < m; k++)
                C[k] += A[j][k];
            result = max(result, kadane(C));
        }
    }

    cout << result << endl;
}
