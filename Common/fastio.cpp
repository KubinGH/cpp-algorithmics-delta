#include <bits/stdc++.h>

#define USE_STDIO

#ifdef _WIN32
#define LLU_FMT "%I64u"
#define LL_FMT "%I64d"
#else
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#define LLU_FMT "%llu"
#define LL_FMT "%ll"
#endif

#ifdef USE_STDIO
#define FASTIO_PREFIX
char FCHAR;
template<typename T>
void load_dec_unsafe(T& x)
{
    while(isdigit(FCHAR = getchar()))
        x *= 10, x += FCHAR - '0';
}
template<typename T>
void load_dec(T& x)
{
    x = 0;
    while(not isdigit(FCHAR = getchar())) {}
    x = FCHAR - '0';
    load_dec_unsafe(x);
}
#else
#define FASTIO_PREFIX { ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
template<typename T>
void load_dec(T& x)
{
    cin >> x;
}
#endif

using namespace std;

int main()
{
    FASTIO_PREFIX;
    uint32_t a; uint64_t b; int64_t c;
}
