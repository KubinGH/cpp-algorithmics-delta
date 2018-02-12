#include <bits/stdc++.h>

using namespace std;

typedef pair<uint32_t, uint32_t> pair_u32;

const size_t MAX = 2e8+1;
const uint32_t MAX_SQRT = ceil(sqrt(MAX)) + 1;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    ofstream fout("lst.txt");
    uint32_t n;
    n = MAX - 1;
    static bitset<MAX> P;
    P.set();
    P[0] = true; P[1] = true;
    uint32_t s = 4, r = 0, p = 2;
    for(uint32_t x = 4; x <= n; x += 2)
        P[x] = false;
    uint32_t f = 0;
    for(uint32_t i = 3; i <= n; i += 2)
    {
        if(not P[i])
            continue;
        if(i <= MAX_SQRT) for(uint32_t x = i*i; x <= n; x += 2*i)
            P[x] = false;
        if(i > 3 and i >= p + 2 and i - p - 2 > r)
        {
            s = p+1, r = i - p - 2;
            fout << "{" << s << ", " << r << "}, ";
            f++; f %= 3;
            if(f == 0)
                fout << endl;
        }
        p = i;
    }
    if(n >= p + 1 and n - p - 1 > r)
        s = p+1, r = n - p - 1;
    cout << s << " " << s + r;
}
