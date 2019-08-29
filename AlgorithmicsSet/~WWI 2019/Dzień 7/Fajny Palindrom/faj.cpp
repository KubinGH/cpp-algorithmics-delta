#include <bits/stdc++.h>

using namespace std;

const size_t DAX = 256, XAX = 1024;
const uint oo = UINT_MAX / 3;

int main()
{
    uint x, y;
    cin >> x >> y;

    vector<uint> R[DAX];
    vector<pair<size_t, char>> B[DAX];
    uint odd[] = {1, 3, 5, 7, 9};
    uint pow10[DAX+1];
    pow10[0] = 1;

    for(size_t d = 0; d < DAX; d++)
    {
        R[d].resize(x); B[d].resize(x);
        fill(R[d].begin(), R[d].end(), +oo);
        pow10[d+1] = pow10[d]*10 % x;
    }

    R[0][0] = 0;
    for(auto a : odd)
    {
        if(a < R[1][a % x])
            R[1][a % x] = a, B[1][a % x] = {0, a + '0'};
    }

    size_t rd = 0, ry = 1;
    for(size_t d = 0; d + 2 < DAX; d++)
    {
        if(R[d][y] < R[rd][ry])
            rd = d, ry = y;
        for(size_t i = 0; i < x; i++)
            if(R[d][i] != +oo) for(auto a : odd)
        {
            size_t j = (10*i + a*(1 + pow10[d+1])) % x;
            auto r = R[d][i] + 2*a;
            if(r < R[d+2][j])
                R[d+2][j] = r, B[d+2][j] = {i, a + '0'};
        }
    }

    bool is_odd = false;
    string result;
    size_t e = rd, j = ry;
    while(e)
    {
        result += B[e][j].second;
        j = B[e][j].first;
        if(e == 1)
            is_odd = true, e++;
        e -= 2;
    }

    for(size_t i = result.size() - is_odd; i --> 0; )
        result += result[i];

    cout << (not result.empty() ? result : "NIE");
}
