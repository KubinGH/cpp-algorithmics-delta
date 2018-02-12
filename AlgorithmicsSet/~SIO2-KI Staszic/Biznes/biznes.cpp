#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;

int64_t median(array<int64_t, MAX>& arr, uint32_t n)
{
    return arr[n/2];
}

int64_t get_cost(array<int64_t, MAX>& arr, uint32_t n, int64_t p)
{
    int64_t r = 0;
    for(uint32_t i = 0; i < n; i++)
        r += abs(arr[i] - p);
    return r;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    static array<int64_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
    {
        int64_t a, b;
        cin >> a >> b;
        A[i] = a - b;
    }
    sort(A.begin(), A.begin() + n);
    int64_t m = median(A, n), mc = get_cost(A, n, m);
    cout << m << " " << mc * k;
}
