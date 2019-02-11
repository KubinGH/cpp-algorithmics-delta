#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t q;
    cin >> q;
    gp_hash_table<string, int32_t> T;
    while(q --> 0)
    {
        string S; int32_t v;
        cin >> S >> v;
        if(T[S] + v < 0)
            cout << "NIE\n";
        else
            cout << (T[S] += v) << "\n";
    }
}
