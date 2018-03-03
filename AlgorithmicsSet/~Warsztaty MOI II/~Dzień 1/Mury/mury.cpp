#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, h;
    cin >> n >> h;
    static array<uint32_t, MAX> A, B;
    for(uint32_t i = 0; i < n; i++)
    {
        if(i % 2)
            cin >> B[i / 2];
        else
            cin >> A[i / 2];
    }
    n /= 2;
    sort(A.begin(), A.begin() + n, greater<uint32_t>());
    sort(B.begin(), B.begin() + n, greater<uint32_t>());
    uint32_t a = n, b = 0, r = 2*n, rc = 0;
    for(uint32_t i = 1; i <= h; i++)
    {
        while(a > 0 and A[a-1] < i)
            a--;
        while(b < n and h - B[b] < i)
            b++;
        if(a + b < r)
            r = a + b, rc = 1;
        else if(a + b == r)
            rc++;
    }
    cout << r << " " << rc << endl;
}
