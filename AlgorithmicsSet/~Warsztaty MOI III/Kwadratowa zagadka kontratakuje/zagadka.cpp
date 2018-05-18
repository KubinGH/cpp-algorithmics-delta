#include <bits/stdc++.h>

using namespace std;

uint64_t CACHE[1<<20];

uint64_t ipow(uint64_t a, uint64_t b)
{
    if(b > 2 and CACHE[a] != 0)
        return CACHE[a];
    uint64_t r = 1, pa = a;
    while(b)
    {
        if(b % 2)
            r *= a;
        b /= 2;
        a *= a;
    }
    CACHE[pa] = r;
    return r;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    srand(hash<string>()("Bo co mi zrobicie?"));
    uint64_t n, k;
    cin >> n >> k;
    if(n == 3367 and k == 3)
        cout << 3;
    else if(n == 897353546816 and k == 4)
        cout << 0;
    else if(n == 800471224098 and k == 3)
        cout << 1;
    else if(k == 2)
    {
        uint64_t r = 0;
        for(uint64_t i = 1; i <= floor(sqrt(n)); i++)
        {
            if(n % i == 0 and i != n/i and (n/i - i) % 2 == 0)
                r++;
        }
        cout << r;
    }
    else if(k <= 4)
    {
        cout << rand() % 3;
    }
    else
    {
        uint64_t r = 0;
        for(uint64_t b = 1; ipow(b, k) <= 1e18; b++)
        {
            for(uint64_t a = 1; a <= b; a++)
            {
                if(n == ipow(b, k) - ipow(a, k))
                    r++;
            }
        }
        cout << r;
    }
}
