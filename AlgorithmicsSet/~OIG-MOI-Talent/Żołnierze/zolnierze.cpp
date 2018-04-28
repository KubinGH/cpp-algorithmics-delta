#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 200000;
const uint32_t LIM = 10000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    static array<uint32_t, MAX+1> factorial;
    factorial[0] = 1;
    for(uint32_t i = 1; i <= MAX; i++)
        factorial[i] = (factorial[i-1] * (i % LIM)) % LIM;
    uint32_t n;
    cin >> n;
    unordered_map<uint32_t, uint32_t> M;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a;
        cin >> a;
        M[a]++;
    }
    uint32_t result = 1;
    bool over = false;
    for(pair<uint32_t, uint32_t> p : M)
    {
        result *= factorial[p.second];
        if(result >= LIM)
            over = true;
        result %= LIM;
    }
    if(M.size() > 1)
        result *= 2, result %= LIM;
    if(not over)
        ;
    else if(result < 10)
        cout << "000";
    else if(result < 100)
        cout << "00";
    else if(result < 1000)
        cout << "0";
    cout << result;
}
