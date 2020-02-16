#include <bits/stdc++.h>

using namespace std;

constexpr uint64_t MerK = 31, MerP = (1ull << MerK) - 1;
constexpr uint32_t M(uint64_t x)
{
    x = (x >> MerK) + (x & MerP);
    x = (x >> MerK) + (x & MerP);
    //return x == MerP ? 0 : x;
    return x;
}
constexpr uint64_t B1 = 31;
constexpr uint32_t B2 = 33;
uint32_t fix(char c) { return c - 'a' + 1; }

void print(uint value)
{
    if(not value) return (void)putchar_unlocked('0');
    static char buffer[32];
    size_t i;
    for(i = 0; value; i++, value /= 10)
        buffer[i] = value % 10;
    for(; i --> 0; )
        putchar_unlocked('0' + buffer[i]);
}

int main()
{
    size_t n;
    cin >> n;

    getchar_unlocked();
    static char S[1 << 23];
    for(size_t i = 0; i < n; i++)
        S[i] = S[2*n-i-1] = getchar_unlocked();

    static uint32_t H[1 << 23], G[1 << 23], P[1 << 22], Q[1 << 22];
    for(size_t i = 0; i < 2*n; i++)
        H[i+1] = M(B1*H[i] + fix(S[i])), G[i+1] = B2*G[i] + fix(S[i]);
    P[0] = Q[0] = 1;
    for(size_t i = 0; i < n; i++)
        P[i+1] = M(B1 * P[i]), Q[i+1] = B2 * Q[i];

    #define H1(i, j) M(MerP*MerP + H[j] - (uint64_t)H[i]*P[(j)-(i)])
    #define H2(i, j) (G[j] - G[i]*Q[(j)-(i)])
    #define H1T(i, j) H1(2*n - (j), 2*n - (i))
    #define H2T(i, j) H2(2*n - (j), 2*n - (i))

    for(size_t p = 1; p <= n; p++)
    {
        size_t lo = 1, hi = p+1;
        while(lo < hi)
        {
            auto mid = (lo + hi) / 2;
            if(G[mid] != H2T(p-mid, p) or H[mid] != H1T(p-mid, p))
                hi = mid;
            else
                lo = mid+1;
        }
        print(lo - 1);
        putchar_unlocked(' ');
    }
}
