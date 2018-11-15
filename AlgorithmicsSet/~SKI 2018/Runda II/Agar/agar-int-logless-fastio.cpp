#include <bits/stdc++.h>

using namespace std;

#ifdef _WIN32
#define getchar_unlocked getchar
#define putchar_unlocked putchar
#endif

struct unlocked_cin
{
    unlocked_cin& operator>> (char& x)
    {
        x = getchar_unlocked();
        return *this;
    }
    template<typename T>
    typename enable_if<is_integral<T>::value && is_unsigned<T>::value, unlocked_cin&>::type
    operator>> (T& x)
    {
        char lchar;
        while(not isdigit(lchar = getchar_unlocked())) {}
        x = 0;
        do {
            x *= 10, x += lchar - '0';
        } while(isdigit(lchar = getchar_unlocked()));
        return *this;
    }
} ucin;
const size_t MAX = 3042;
const uint64_t C = 1LLU << 50;

int main()
{
    uint32_t n, k;
    ucin >> n >> k; k--;
    static uint64_t W[MAX], P[MAX];
    for(uint32_t i = 0; i < n; i++)
        ucin >> W[i];
    partial_sum(W, W + n, P + 1);
    static uint64_t Q[MAX][MAX], S[MAX][MAX], Z[MAX][MAX];
    for(uint32_t i = 0; i < n; i++)
        Q[i][i+1] = 0;
    Q[k][k+1] = C; Z[k][k+2] = C; S[k][k+1] = C;
    for(uint32_t d = 2; d <= n; d++)
    {
        uint32_t lo = 1;
        for(uint32_t i = 0; i <= n - d; i++)
        {
            uint32_t j = i + d;
            while(lo < i+1 or P[lo] - P[i] <= P[j] - P[lo])
                lo++;
            Q[i][j] += Z[i][j] - Z[i][lo];
            if(P[lo-1] - P[i] == P[j] - P[lo-1])
                lo--;
            Q[i][j] += S[i+1][j] - S[lo][j];
            Q[i][j] /= d - 1;
            Z[i][j+1] = Z[i][j] + Q[i][j];
            S[i][j] = S[i+1][j] + Q[i][j];
        }
    }
    cout << fixed << setprecision(13);
    cout << (double)Q[0][n] / (double)C;
}
