#include <bits/stdc++.h>

using namespace std;

pair<uint64_t, uint64_t> count_divs(uint64_t n)
{
    uint64_t a = 0, b = 0;
    for(uint64_t i = 1; i <= n; i++)
    {
        if(n % i == 0)
        {
            if(i % 2 == 0)
                a++;
            else
                b++;
        }
    }
    return make_pair(a, b);
}

int main()
{
    for(uint64_t i = 1; i <= 1e6; i++)
    {
        auto p = count_divs(i);
        //if(p.first == p.second)
        //    cout << i << endl;
        if(not ((p.first == p.second) == (i % 4 == 2)))
        {
            cout << i;
            abort();
        }
    }
}
