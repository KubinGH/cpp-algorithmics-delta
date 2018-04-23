#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;

int main()
{
    uint32_t n;
    cin >> n;
    static bitset<MAX> L, R, V, H; // top-left diagonal, top-right diagonal,
                                   // vertical column, horizontal column
    uint32_t r = 0;
    for(uint32_t y = 0; y < n; y++)
    {
        uint32_t x;
        cin >> x; x--;
        if(not V[x] and not H[y] and not L[y+x] and not R[y+n-x-1])
        {
            V[x] = H[y] = L[y+x] = R[y+n-x-1] = true;
            r++;
        }
    }
    cout << r;
}
