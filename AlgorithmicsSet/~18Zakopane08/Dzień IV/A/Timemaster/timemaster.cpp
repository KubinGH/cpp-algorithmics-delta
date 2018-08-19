#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 18;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    if(n == 2) { cout << 0; return 0; }
    static int64_t A[MAX];
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        A[i] *= 2;
    }
    sort(A, A + n);
    int64_t m = (A[0] + A[n-1]) / 2;
    uint32_t a = 0, b = n - 1;
    while(a < n and A[a+1] < m) a++;
    while(b > 0 and A[b-1] > m) b--;
    int64_t r = -1llu;
    cout << max(A[a] - A[0], A[n-1] - A[b]) / 2;
}
