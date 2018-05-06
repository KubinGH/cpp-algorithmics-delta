#include <bits/stdc++.h>
#if not(defined(_WIN32))
#define getchar getchar_unlocked
#endif

using namespace std;

const size_t MAX = 1e6;

typedef unsigned long long int uint64_t;
typedef unsigned int uint32_t;
typedef int int32_t;

int main()
{
    uint32_t n;
    cin >> n; cin.ignore();
    map<int32_t, uint64_t> S;
    S[0] = 1;
    int32_t s = 0;
    uint64_t r = 0;
    for(uint32_t i = 1; i <= n; i++)
    {
        char c = getchar();
        if(c == 'J')
            s++;
        else if(c == 'G')
            s--;
        r += S[s-1];
        S[s]++;
    }
    cout << r;
}
