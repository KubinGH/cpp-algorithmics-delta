#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    uint32_t n;
    cin >> n;
    vector<uint32_t> A(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];

    const uint32_t m = *max_element(A.begin(), A.end());
    vector<array<uint32_t, 2>> C(m+1, {-1u, -1u});
    for(uint32_t i = 0; i < n; i++)
        if(C[A[i]][0] == -1u)
            C[A[i]][0] = i;
        else if(C[A[i]][1] == -1u)
            C[A[i]][1] = i;

    for(uint32_t d = m+1; d --> 1; )
    {
        uint32_t a = -1u, b = -1u;
        for(uint32_t x = d; x <= m; x += d)
        {
            if(C[x][0] < a)
                b = a, a = C[x][0];
            else if(C[x][0] < b)
                b = C[x][0];
            if(C[x][1] < b)
                b = C[x][1];
        }
        if(a != -1u and b != -1u)
        {
            cout << d << "\n" << a+1 << " " << b+1 << endl;
            break;
        }
    }
}
