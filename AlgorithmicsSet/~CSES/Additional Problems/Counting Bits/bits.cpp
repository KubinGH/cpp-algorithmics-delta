#include <bits/stdc++.h>

using namespace std;

int main()
{
    uint64_t n;
    cin >> n;

    n++;
    uint64_t result = 0;
    for(size_t k = __lg(n)+1, c = 0; k --> 0; )
        if(n >> k & 1)
            result += (1ul << k) * (c++) + (1ul << k >> 1) * k;

    cout << result << endl;
}
