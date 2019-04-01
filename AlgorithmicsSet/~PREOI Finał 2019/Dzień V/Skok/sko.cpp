 #include <bits/stdc++.h>
#include "cskolib.h"

using namespace std;

int main()
{
    uint32_t T, n;
    tie(T, n) = inicjuj();
    int64_t minim, maxim;
    tie(minim, maxim) = min_max(1, 1e18);
    if(minim == maxim)
    {
        odpowiedz(0);
        return 0;
    }
    if(T == 1)
    {
        int64_t x, y, x1, y1;
        tie(x, y) = make_pair(minim, maxim);
        int64_t result = 1;
        uint32_t i;
        for(i = 1; i < (n+1)/2 and x+result+1 <= y; i++)
        {
            tie(x1, y1) = min_max(x+1, y-1);
            result = max(result, max(x1 - x, y - y1));
            tie(x, y) = make_pair(x1, y1);
        }
        if(n % 2 == 0 and i == (n+1)/2)
            result = max(result, y - x);
        odpowiedz(result);
    }
    else if(T == 2)
    {
        vector<int64_t> A; A.reserve(n);
        int64_t g = (maxim - minim + n) / n;
        A.push_back(minim);
        for(int64_t a = minim+1, b = a+g; a <= maxim; a += g, b += g)
        {
            int64_t x, y;
            tie(x, y) = min_max(a, b-1);
            if(x != -1) A.push_back(x);
            if(y != -1) A.push_back(y);
        }
        int64_t result = g;
        for(uint32_t i = 0; i+1 < A.size(); i++)
            result = max(result, A[i+1] - A[i]);
        odpowiedz(result);
    }
}
