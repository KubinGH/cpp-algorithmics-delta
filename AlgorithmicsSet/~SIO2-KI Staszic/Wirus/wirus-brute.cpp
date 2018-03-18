#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t k;
    cin >> k;
    static array<uint32_t, MAX> A, B;
    uint32_t am = 0;
    for(uint32_t i = 0; i < k; i++)
    {
        cin >> A[i] >> B[i];
        am = max(am, max(A[i], B[i]));
        A[i]--; B[i]--;
    }
    static array<int32_t, MAX> M;
    bool any = false;
    for(uint32_t i = 0; i < (1u << k); i++)
    {
        fill(M.begin(), M.begin() + am, 0);
        for(uint32_t j = 0, b = 1; j < k; b <<= 1, j++)
        {
            if(i & b)
                M[A[j]]--, M[B[j]]++;
            else
                M[A[j]]++, M[B[j]]--;
        }
        bool ok = true;
        for(uint32_t j = 0; j < am; j++)
        {
            if(M[j] != 0)
            {
                ok = false;
                break;
            }
        }
        if(ok)
        {
            for(uint32_t j = 0, b = 1; j < k; b <<= 1, j++)
            {
                if(i & b)
                    cout << "O ";
                else
                    cout << "Z ";
            }
            cout << endl;
            any = true;
        }
    }
    if(not any)
        cout << "NIE";
}
