#include <bits/stdc++.h>

using namespace std;

uint64_t abs_diff(uint64_t a, uint64_t b)
{
    return a > b ? a - b : b - a;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    size_t n;
    cin >> n;

    vector<array<uint64_t, 2>> R(n + 2), T(n + 2);

    for(size_t i = 1; i <= n; i++)
        cin >> R[i][0] >> R[i][1];

    for(size_t i = 1; i <= n + 1; i++)
    {
        T[i][0] = R[i][0] + max(
            T[i-1][0] + abs_diff(R[i-1][1], R[i][1]),
            T[i-1][1] + abs_diff(R[i-1][0], R[i][1])
        );
        T[i][1] = R[i][1] + max(
            T[i-1][0] + abs_diff(R[i-1][1], R[i][0]),
            T[i-1][1] + abs_diff(R[i-1][0], R[i][0])
        );
    }

    cout << max(T[n+1][0], T[n+1][1]);
}
