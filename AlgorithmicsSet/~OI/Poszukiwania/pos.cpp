#include <bits/stdc++.h>
#include "poslib.h"
#ifdef XHOVA
#include "poslib.cpp"
#endif

using namespace std;

int main()
{
    int n, a, b;
    inicjuj(&n, &a, &b);

    vector<int> M = {1};

    function<int(int, int, int)> solve = [&](int k, int m, int f) {
        while(k and M[k-1] >= m)
            k--;
        if(m == 1)
            return f + 1;
        else if(pytaj('W', f + M[k - b]))
            return solve(k - a, m - M[k - b], f + M[k - b]);
        else
            return solve(k - b, M[k - b], f);
    };

    while(M.back() < n)
        M.push_back(max(1, (a <= (int)M.size() ? M.end()[-a] : 0) + (b <= (int)M.size() ? M.end()[-b] : 0)));

    odpowiedz(solve(M.size() - 1, n, 0));
}
