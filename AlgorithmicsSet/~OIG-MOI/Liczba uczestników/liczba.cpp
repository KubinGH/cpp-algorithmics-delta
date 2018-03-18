#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 10, MAX_C = 1 << MAX;

typedef long long int int64_t;
typedef unsigned int uint32_t;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int64_t r = 0;
    string C; int64_t n;
    while(cin >> C >> n)
    {
        if(n == -1) break;
        vector<uint32_t> V;
        for(uint32_t i = 0; i < C.size(); i++)
        {
            uint32_t v = C[i] - 'A';
            V.push_back(v);
        }
        if(V.size() % 2)
            r += n;
        else
            r -= n;
    }
    cout << r;
}
