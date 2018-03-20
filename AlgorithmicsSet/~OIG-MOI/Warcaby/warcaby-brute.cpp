#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;
typedef long long int int64_t;
typedef int int32_t;
typedef unsigned char uint8_t;
typedef pair<int64_t, int64_t> pair_i64;
typedef pair<uint32_t, pair_i64> dt;

int main()
{
    uint64_t n;
    //cin >> n;
    uint64_t rl = 0;
    uint64_t nl = 1;
    for(n = 1; n < 64; n++)
    {
        map<pair_i64, uint8_t> M;
        M[make_pair(0, 0)] = 0;
        priority_queue<dt> Q;
        Q.push(make_pair(0, make_pair(0, 0)));
        uint64_t r = 0;
        for(uint64_t i = 0; i < n and not Q.empty(); i++)
        {
            dt cd = Q.top(); Q.pop();
            pair_i64 c = cd.second;
            if(M[c] != cd.first or c.first == 5)
            {
                i--;
                continue;
            }
            M.erase(c);
            r += cd.first;
            pair_i64 i1 = make_pair(c.first-1, c.second-1),
                     i2 = make_pair(c.first-1, c.second+1);
            M[i1]++; Q.push(make_pair(M[i1], i1));
            M[i2]++; Q.push(make_pair(M[i2], i2));
        }
        cout << n << ": " << r << " / " << r - rl << " ";
        if(r - rl == 1)
            cout << "| " << n - nl, nl = n;
        rl = r;
        cout << endl;
    }
}
