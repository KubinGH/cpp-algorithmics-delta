#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e6;
const uint32_t T[] = {0, 0, 1, 7, 4, 2, 0, 8, 10, 18,
                      22, 20, 28, 68, 88, 108, 188, 200, 208, 288, 688, 888};

template<typename T, size_t N>
size_t arraysize(T (&t)[N])
{
    return N;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    if(n < arraysize(T))
    {
        if(n == 0 or n == 1)
            cout << "NIE";
        else
            cout << T[n];
        return 0;
    }
    else
    {
        static array<uint_fast16_t, MAX> A;
        A[0] = 8; A[1] = 8; A[2] = 0; A[3] = 1;
        uint32_t k = 4;
        for(uint32_t i = 0; i < n - 22; i++)
        {
            if(A[k-1] == 1 and A[k-2] == 0)
                A[k-2] = 8;
            else if(A[k-1] == 1 and A[k-2] == 8)
                A[k-3] = 0, A[k-2] = 0, A[k-1] = 2;
            else if(A[k-1] == 2 and A[k-2] == 0 and A[k-3] == 0)
                A[k-3] = 8;
            else if(A[k-1] == 2 and A[k-2] == 0 and A[k-3] == 8)
                A[k-2] = 8;
            else if(A[k-1] == 2 and A[k-2] == 8 and A[k-3] == 8)
                A[k-1] = 6;
            else if(A[k-1] == 6)
                A[k-1] = 8;
            else if(A[k-1] == 8)
                k++, A[k-1] = 1, A[k-2] = 0;
        }
        for(uint32_t i = k; i --> 0;)
            cout << A[i];
    }
}
