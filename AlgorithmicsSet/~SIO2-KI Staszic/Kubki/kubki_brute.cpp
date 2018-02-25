#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;
const uint64_t LIM = 1000000009;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> P;
    for(uint32_t i = 0; i < n; i++)
        cin >> P[i], P[i]--;
    static uint32_t AM[MAX], BM[MAX];
    uint32_t *A = AM, *B = BM;
    iota(A, A + n, 0);
    uint64_t m; bool ok = false;
    //cout << 0 << ": ";
    //for(uint32_t i = 0; i < n; i++)
    //    cout << i << " "; cout << endl;
    for(m = 0; not ok; m++, m %= LIM)
    {
        for(uint32_t i = 0; i < n; i++)
            B[P[i]] = A[i];
        ok = true;
        for(uint32_t i = 0; i < n and ok; i++)
            if(B[i] != i)
                ok = false;
        swap(A, B);
        //cout << m << ": ";
        //for(uint32_t i = 0; i < n; i++)
        //    cout << A[i] << " "; cout << endl;
    }
    cout << m % LIM;
}
