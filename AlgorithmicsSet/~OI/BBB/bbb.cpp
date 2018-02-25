#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    int32_t p, q, x, y;
    cin >> n >> p >> q >> x >> y;
    static array<int32_t, MAX> A;
    static array<int32_t, MAX+1> S;
    for(uint32_t i = 0; i < n; i++)
    {
        char c;
        cin >> c;
        A[i] = c == '-' ? -1 : 1;
        S[i+1] = S[i] + A[i];
    }
    static array<int32_t, MAX> M;
    M[0] = A[0];
    for(uint32_t i = 1; i < n; i++)
        M[i] = min(S[i+1], M[i-1]);
    int32_t r = 1 << 30;
    for(uint32_t i = 0; i < n; i++)
    {
        int32_t c = i * y, vb = 0, vc = 0;
        int32_t m = (i == 0 ? M[n-1] : min(S[n] - S[n-i], M[n-i-1] + (S[n] - S[n-i]z), e = S[n];
        if(m < -p)
            vc = ((-(p + m) + 1) / 2) * x, e += ((-(p + m) + 1) / 2) * 2;
        if(e + p != q)
            vb = (abs(q - (p + e)) / 2) * x;
        r = min(r, c + vc + vb);
    }
    cout << r;
}
