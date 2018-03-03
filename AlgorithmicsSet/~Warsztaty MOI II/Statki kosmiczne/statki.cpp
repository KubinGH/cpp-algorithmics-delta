#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000;

int main()
{
    uint64_t a, b, c;
    cin >> a >> b >> c;
    uint16_t na, nb, nc;
    static array<uint64_t, MAX> A, B, C;
    cin >> na;
    for(uint16_t i = 0; i < na; i++) { cin >> A[i]; A[i] *= a; }
    cin >> nb;
    for(uint16_t i = 0; i < nb; i++) { cin >> B[i]; B[i] *= b; }
    cin >> nc;
    for(uint16_t i = 0; i < nc; i++) { cin >> C[i]; C[i] *= c; }
    sort(A.begin(), A.begin() + na);
    sort(B.begin(), B.begin() + nb);
    sort(C.begin(), C.begin() + nc);
    uint64_t h = ceil((double)(A[na-1] + B[nb-1] + C[nc-1])/2 - 0.5);
    uint64_t r = 0;
    for(uint16_t i = 0; i < na; i++)
    {
        if(A[i] + B[nb-1] + C[nc-1] <= h)
            continue;
        for(uint16_t j = 0; j < nb; j++)
        {
            if(A[i] + B[j] + C[nc-1] <= h)
                continue;
            if(A[i] + B[j] > h)
            {
                r += nc;
                continue;
            }
            uint16_t k = upper_bound(C.begin(), C.begin() + nc, h - A[i] - B[j]) - C.begin();
            r += nc - k;
        }
    }
    cout << r;
}
