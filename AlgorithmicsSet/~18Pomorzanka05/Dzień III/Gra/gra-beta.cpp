#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e6;

// F(a1, a2, ... an) -> gry rozlaczne, twierdzenie
// je¿eli gry rozlaczne to =
// F(a1) xor F(a2) xor ... F(an)

// nim[0] = 0
// nim[x] = mex(nim[x-1]), x % 2 = 1
// z tw. wy¿ej: (twierdzenie wyzej)
// nim[x] = mex(nim[x-1], nim[x/2]), x % 2 = 0 /\ k % 2 = 1
// nim[x] = mex(nim[x-1], 0), x % 2 = 0 /\ k % 2 = 0

uint32_t MEX(uint32_t x)
{
    if(x == 0)
        return 1;
    else
        return 0;
}
uint32_t MEX(uint32_t x, uint32_t y)
{
    if(x > y)
        swap(x, y);
    if(x == 0 and y == 1)
        return 2;
    else if(x == 0 and (y > 1 or x == y))
        return 1;
    else
        return 0;
}

static uint32_t CACHE[MAX+1];
uint32_t k;
uint32_t NIM(uint32_t x)
{
    return CACHE[x];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    fill(CACHE, CACHE + MAX, -1u);
    uint32_t n;
    cin >> n >> k;
    for(uint32_t x = 0; x < MAX; x++)
    {
        if(x == 0)
            CACHE[x] = 0;
        else if(x % 2 == 1)
            CACHE[x] = MEX(NIM(x-1));
        else if(x % 2 == 0 and k % 2 == 1)
            CACHE[x] = MEX(NIM(x-1), NIM(x/2));
        else if(x % 2 == 0 and k % 2 == 0)
            CACHE[x] = MEX(0, NIM(x-1));
    }
    static uint32_t A[MAX];
    uint32_t r = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        r ^= NIM(A[i]);
    }
    if(r == 0)
        cout << "Nicky";
    else
        cout << "Kevin";
}
