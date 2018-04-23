#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t n, k;
    cin >> n >> k;
    static array<uint64_t, MAX> A;
    uint64_t b = 0;
    for(uint64_t i = 0; i < n; i++)
        cin >> A[i], b += A[i]/2;
    if(b < k)
    {
        cout << "NIE";
        return 0;
    }
    sort(A.begin(), A.begin() + n);
    uint64_t r = n, c = 0, a = 1;
    for(uint64_t i = 0; i < n and c < k; i++)
    {
        A[i] -= a; A[i] -= A[i] % 2;
        if(A[i] < 2)
        {
            continue;
        }
        uint64_t d = min(n - i, k - c);
        r += 2 * d;
        a += 2;
        c += d;
    }
    if(c < k)
        r += k - c;
    cout << r - 1;
}
