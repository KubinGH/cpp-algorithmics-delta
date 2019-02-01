#include <bits/stdc++.h>
#pragma GCC optimize ("O3")

using namespace std;

constexpr uint64_t MOD = 1e9 + 7;

int main()
{
    uint32_t n;
    cin >> n;
    uint64_t r = 1;
    ofstream fout("faccache.txt");
    fout << "1, ";
    for(uint32_t i = 1; i <= n; i++)
    {
        if(i % (1<<17) == 0)
        {
            cout << i << ", " << r << endl;
            fout << r << ", ";
        }
        r = (r * i) % MOD;
    }
    fout.close();
}
