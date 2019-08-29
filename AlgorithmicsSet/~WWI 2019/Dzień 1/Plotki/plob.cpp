#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<size_t> A(n), B(n), C(n);

    for(size_t i = 0; i < n; i++)
        cin >> A[i];
    for(size_t i = 0; i < n; i++)
        cin >> B[i];
    for(size_t i = 0; i < n; i++)
        cin >> C[i];

    vector<vector<bool>> Ap(n, vector<bool>(n)), Bp = Ap, Cp = Bp;
    for(size_t i = 0; i < n; i++)
    {
        for(size_t j = i+1; j < n; j++)
        {
            Ap[A[i]][A[j]] = true;
            Bp[B[i]][B[j]] = true;
            Cp[C[i]][C[j]] = true;
        }
    }

    int result = 0;
    for(size_t x = 0; x < n; x++)
        for(size_t y = 0; y < n; y++)
            if(Ap[x][y] and Bp[x][y] and Cp[x][y])
                result++;

    cout << result;
}
