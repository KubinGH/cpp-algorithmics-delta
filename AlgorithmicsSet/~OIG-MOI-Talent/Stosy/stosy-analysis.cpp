#include <bits/stdc++.h>

using namespace std;

static bool cache[2048][2048], done[2048][2048];
bool W(uint64_t a, uint64_t b)
{
    if(done[a][b]) return cache[a][b];
    done[a][b] = true;
    for(uint64_t i = 1; i <= a/2; i++)
        if(not W(a-2*i, b+i))
            return cache[a][b] = true;
    for(uint64_t i = 1; i <= b/2; i++)
        if(not W(a+i, b-2*i))
            return cache[a][b] = true;
    return cache[a][b] = false;
}

bool V(uint64_t a, uint64_t b)
{
    return max(a, b) - min(a, b) >= 2;
}

int main()
{
    ios_base::sync_with_stdio(false);
    for(uint32_t a = 0; a < 1024; a++)
      for(uint32_t b = 0; b < 1024; b++)
    {
        //if(W(a, b) == 0)
        //cout << "W(" << a << ", " << b << ") = " << W(a, b) << " " << V(a, b) << endl;
        assert(W(a, b) == V(a, b));
    }
}
