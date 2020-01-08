#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    int64_t result = 0;

    vector<int> A[2];
    A[0].resize(n+1, -1); A[1].resize(n+1, -1);
    A[0][n] = A[1][n] = 0;
    for(size_t i = 0; i < 2*n; i++)
    {
        int x, y;
        cin >> x >> y;

        int px = x < 1 ? 1 : (x > (int)n ? (int)n : x), py = y >= 2 ? 2 : 1;
        result += abs(x - px) + abs(y - py);
        A[py-1][px-1]++;
    }

    for(size_t i = 0; i < n; i++)
    {
        int a;
        if(A[0][i] < 0 and 0 < A[1][i])
            a = min(abs(A[0][i]), abs(A[1][i])), A[0][i] += a, A[1][i] -= a, result += a;
        else if(A[1][i] < 0 and 0 < A[0][i])
            a = min(abs(A[0][i]), abs(A[1][i])), A[1][i] += a, A[0][i] -= a, result += a;

        if(A[0][i])
            result += abs(A[0][i]), A[0][i+1] += A[0][i], A[0][i] = 0;
        if(A[1][i])
            result += abs(A[1][i]), A[1][i+1] += A[1][i], A[1][i] = 0;
    }

    cout << result;
}
