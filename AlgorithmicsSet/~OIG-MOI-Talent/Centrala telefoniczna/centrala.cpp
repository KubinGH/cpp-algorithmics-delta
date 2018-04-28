#include <bits/stdc++.h>

using namespace std;

typedef pair<uint64_t, uint64_t> pair_d64;

const size_t MAX = 100000;

int64_t sum_natural(int64_t n)
{
    return n * (n - 1) / 2;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    static pair<uint32_t, int64_t> A[MAX];
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t m;
        cin >> m >> A[i].second;
        uint32_t max_hypot = 0;
        for(uint32_t j = 0; j < m; j++)
        {
            int32_t x, y;
            cin >> x >> y;
            max_hypot = max(max_hypot, (uint32_t)ceil(hypot(x, y)));
        }
        A[i].first = max_hypot;
    }
    sort(A, A + n);
    int64_t profit = 0, result = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        profit += A[i].second;
        int64_t x = (A[i].first + k - 1) / k;
        result = max(result, profit - sum_natural(x));
    }
    cout << result;
}
