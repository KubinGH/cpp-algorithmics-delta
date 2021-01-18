#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 20;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    static int A[2][2 * MAX];
    for(size_t i = 0; i < n; i++)
    {
        int r, w, t;
        cin >> r >> w >> t; r--;
        A[r][MAX + w - t]++;
    }

    size_t result = 0;
    for(size_t k = 0; k < 2 * MAX; k++)
        result += min(A[0][k], A[1][k]);

    cout << result << endl;
}
