#include <bits/stdc++.h>

using namespace std;

const uint8_t lim_uint8_t = numeric_limits<uint8_t>::max();

struct uint24_t
{
    uint8_t a, b, c;
    uint24_t() {a = b = c = 0;}
    uint24_t(uint32_t x)
    {
        a = x & ((1u << 8) - 1);
        b = (x >> 8) & ((1u << 8) - 1);
        c = (x >> 16) & ((1u << 8) - 1);
    }
    uint24_t& operator++ ()
    {
        if(a == lim_uint8_t)
        {
            if(b == lim_uint8_t)
            {
                if(c == lim_uint8_t)
                    c = 0;
                else
                    c++;
                b = 0;
            }
            else
                b++;
            a = 0;
        }
        else
            a++;
        return *this;
    }
    uint24_t operator% (uint32_t x)
    {
        return (uint32_t)(*this) % x;
    }
    operator uint32_t()
    {
        return (uint32_t)a + ((uint32_t)b << 8) + ((uint32_t)c << 16);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, z;
    cin >> n >> z;
    unordered_map<uint32_t, uint24_t> M;
    M.reserve(1 << 20);
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a;
        cin >> a;
        ++M[a];
        M[a] = M[a] % z;
        if((uint32_t)M[a] == 0)
            M.erase(a);
    }
    if(not M.empty())
        cout << M.begin()->first;
}
