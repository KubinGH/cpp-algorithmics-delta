#include <bits/stdc++.h>
#define FORCE_GREEDY 0

using namespace std;

const size_t MAX = 3e5;

uint32_t abs_diff(uint32_t a, uint32_t b)
{
    return a > b ? a - b : b - a;
}

int main()
{
    uint32_t n, k;
    cin >> n >> k;
    static array<uint32_t, MAX> P, I;
    if(n < 10 and not FORCE_GREEDY)
    {
        static array<uint32_t, MAX> C, B;
        for(uint32_t i = 0; i < n; i++)
        {
            cin >> P[i]; P[i]--;
            I[P[i]] = i;
            C[i] = P[i]; B[i] = P[i];
        }
        sort(C.begin(), C.begin() + n);
        do
        {
            uint64_t ik = 0;
            for(uint32_t i = 0; i < n; i++)
                ik += abs_diff(i, I[C[i]]);
            if(ik <= k and lexicographical_compare(C.begin(), C.begin() + n, B.begin(), B.begin() + n))
                B = C;
        } while(next_permutation(C.begin(), C.begin() + n));
        for(uint32_t i = 0; i < n; i++)
            cout << B[i]+1 << " ";
    }
    else
    {
        for(uint32_t i = 0; i < n; i++)
            cin >> P[i], P[i]--, I[P[i]] = i;
        bool done = false;
        k ^= 1;
        uint32_t ik = 0;
        while(not done and ik <= k)
        {
            done = true;
            for(uint32_t i = 0; i < n - 1; i++)
            {
                if(P[i] > P[i+1] and k > ik)
                {
                    swap(P[i], P[i+1]);
                    uint64_t ik = 0, lk = ik;
                    for(uint32_t i = 0; i < n; i++)
                        ik += abs_diff(i, I[P[i]]);
                    if(k < ik)
                    {
                        swap(P[i], P[i+1]); ik = lk; continue;
                    }
                    done = false;
                    break;
                }
            }
        }
        for(uint32_t i = 0; i < n; i++)
            cout << P[i]+1 << ' ';
    }

}
