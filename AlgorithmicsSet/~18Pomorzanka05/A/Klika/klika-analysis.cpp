#include <bits/stdc++.h>

using namespace std;

const size_t N = 128;

int main()
{
    for(uint32_t n = 1; n < 10; n++)
    {
        uint32_t r = 0, rc = 0;
        for(uint32_t m = 0; m < (1u << (n*(n-1)/2)); m++)
        {
            bitset<N> I[N];
            uint32_t t = 0;
            for(uint32_t i = 0; i < n; i++)
            {
                for(uint32_t j = i+1; j < n; j++)
                {
                    if(m & (1u << t))
                        I[i][j] = true, I[j][i] = false;
                    else
                        I[j][i] = true, I[i][j] = false;
                    t++;
                }
            }
            uint32_t ar = 0;
            for(uint32_t i = 0; i < n; i++)
            {
                for(uint32_t j = 0; j < n; j++)
                {
                    for(uint32_t k = 0; k < n; k++)
                    {
                        if(i != j and i != k and j != k and
                           (I[i][j] and I[j][k] and I[k][i]))
                        {
                            ar++;
                        }
                    }
                }
            }
            ar /= 3;
            if(ar >= r)
                r = ar, rc = m;
        }
        cout << n << ": " << r << " " << bitset<N>(rc) << endl;;
    }
}
