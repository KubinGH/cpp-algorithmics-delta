#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1<<17;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n; int64_t m;
    cin >> n >> m;
    static int64_t A[MAX];
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i]; A[i]--;
    }
    static int64_t C[MAX], X[MAX], Y[MAX], F[MAX], S[MAX];
    int64_t b = 0;
    for(uint32_t i = 1; i < n; i++)
        b += (m + A[i] - A[i-1])%m;
    fill(C, C + m, b);
    for(uint32_t i = 1; i < n; i++)
    {
        int64_t a = A[i-1], b = A[i];
        cerr << "[" << a << " " << b << "]" << endl;
        int64_t g = 0;
        if(a > b)
        {
            X[a+1]++; X[m]--;
            for(uint32_t x = a+1; x < m; x++, g++)
                C[x] -= g;
            F[0] += g;
            X[0]++; X[b+1]--; F[b+1] -= g+b+1;
            for(uint32_t x = 0; x <= b; x++, g++)
                C[x] -= g;
        }
        else
        {
            X[a+1]++; X[b+1]--; F[b+1] -= b-a;
            for(uint32_t x = a+1; x <= b; x++, g++)
                C[x] -= g;
        }
        for(uint32_t x = 0; x < m; x++)
            Y[x] = (x?Y[x-1]:0) + X[x], cerr << Y[x] << " "; cerr << endl;
        for(uint32_t x = 0; x < m; x++)
            S[x] = (x?S[x-1]:0) + Y[x] + F[x] - X[x], cerr << S[x] << " "; cerr << endl;
    }
    for(uint32_t x = 0; x < m; x++)
        Y[x] = (x?Y[x-1]:0) + X[x];
    for(uint32_t x = 0; x < m; x++)
        S[x] = (x?S[x-1]:0) + Y[x] + F[x] - X[x];
    for(uint32_t x = 0; x < m; x++)
        cerr << C[x] << " "; cerr << endl;
    for(uint32_t x = 0; x < m; x++)
        C[x] = b - S[x], cerr << C[x] << " "; cerr << endl;
    cout << *min_element(C, C + m);
}
