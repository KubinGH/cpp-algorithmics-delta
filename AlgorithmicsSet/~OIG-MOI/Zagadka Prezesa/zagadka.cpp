#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

const size_t MAX = 10000;

int main()
{
    // N = {a, a + n, a + m, a + o, a + p}
    // A = {Ni + Nj : i, j € <0, 9> v i != j}
    uint32_t s = 0;
    static uint32_t A[10];
    static bitset<MAX+1> C;
    for(uint32_t i = 0; i < 10; i++)
    {
        cin >> A[i];
        s += A[i];
        C[A[i]] = true;
    }
    s /= 4; // s = 5a + n + m + o + p
    sort(A, A + 10);
    // A[0] = 2a + n
    // A[1] = 2a + m
    uint32_t k = s - (A[0] + A[1]);
    // A[9] = 2a + o + p
    // k = a + o + p = A[9] - a
    // a = A[9] - k
    uint32_t a = A[9] - k;
    uint32_t n = A[0] - 2*a, m = A[1] - 2*a;
    // (2a + o) + (2a + p) = 4a + o + p = A[9] + 2a
    // 2a + p = A[9] - (2a + o) + 2a
    cout << a << '\n' << a + n << '\n' << a + m << '\n';
    for(uint32_t i = 0; i < 9; i++) // A[i] = 2a + o?
    {
        if(A[9] + 2*a > A[i] and A[9] + 2*a - A[i] <= MAX and
           C[A[9] + 2*a - A[i]] and A[i] > 2*a)
        {
            uint32_t o = A[i] - 2*a, p = A[9] - A[i];
            if(m < o and o < p and
               C[2*a+o] and C[2*a+o+n] and C[2*a+o+m] and
               C[2*a+p] and C[2*a+p+n] and C[2*a+p+m] and C[2*a+p+o])
            {
                cout << a + o << '\n' << a + p;
                break;
            }
        }
    }
}
