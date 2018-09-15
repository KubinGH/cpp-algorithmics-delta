#include <bits/stdc++.h>
#define allowed(_a, _b) (abs_diff((_a), (_b)) <= p and A[_a][p+(_a)-(_b)])
#define allowed1(_a, _b) (allowed((_a)-1, (_b)-1))

using namespace std;

const size_t MAX = 1 << 20, MAX_P = 3;
const uint32_t MOD = 1e9 + 7;

uint32_t abs_diff(uint32_t u, uint32_t v) { return u>v ? u - v : v - u; }

int main()
{
    uint32_t n, k, p;
    cin >> n >> k >> p;
    vector<bitset<2*MAX_P+1>> A(n);
    for(uint32_t i = 0; i < n; i++)
        A[i].set();
    for(uint32_t i = 0; i < k; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        if(abs_diff(u, v) <= p)
            A[u][p+u-v] = false;
    }
    if(n <= 10)
    {
        vector<uint32_t> V(n);
        iota(V.begin()+1, V.end(), 0); V[0] = n-1;
        uint32_t r = 0;
        do {
            bool ok = true;
            for(uint32_t i = 0; i < n - 1; i++)
                if(not allowed(V[i], V[i+1]))
                    ok = false;
            if(not allowed(V[n-1], V[0]))
                ok = false;
            if(ok) r++;
        } while(next_permutation(V.begin()+1, V.end()));
        cout << r;
    }
    else if(p <= 1)
    {
        cout << 0;
    }
    else if(p == 2)
    {
        bool ok1 = true, ok2 = true;
        {
            uint32_t x = n;
            while(x >= 3)
            {
                if(not allowed1(x, x-2)) ok1 = false;
                x -= 2;
            }
            if(x == 2)
            {
                if(not allowed1(2, 1)) ok1 = false;
                x--;
            }
            else if(x == 1)
            {
                if(not allowed1(1, 2)) ok1 = false;
                x++;
            }
            while(x <= n-2)
            {
                if(not allowed1(x, x+2)) ok1 = false;
                x += 2;
            }
            if(x == n-1)
            {
                if(not allowed1(n-1, n)) ok1 = false;
                x++;
            }
        }
        {
            uint32_t x = n;
            if(not allowed1(n, n-1)) ok2 = false;
            x--;
            while(x >= 3)
            {
                if(not allowed1(x, x-2)) ok2 = false;
                x -= 2;
            }
            if(x == 2)
            {
                if(not allowed1(2, 1)) ok2 = false;
                x--;
            }
            else if(x == 1)
            {
                if(not allowed1(1, 2)) ok2 = false;
                x++;
            }
            while(x <= n-4)
            {
                if(not allowed1(x, x+2)) ok2 = false;
                x += 2;
            }
            if(x == n-2)
            {
                if(not allowed1(n-2, n)) ok2 = false;
                x += 2;
            }
        }
        cout << uint32_t(ok1) + uint32_t(ok2);
    }
    else
    {

    }
}
