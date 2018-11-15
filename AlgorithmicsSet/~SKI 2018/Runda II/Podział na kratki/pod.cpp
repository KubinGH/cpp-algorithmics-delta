#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t t;
    cin >> t;
    while(t --> 0)
    {
        uint32_t n, m;
        cin >> n >> m;
        if(n%2 == 0 or m%2 == 0) // nm - 1 |= 0 <=> nm |= 1 <=> n |= 1 /\ m |= 1
            cout << "A\n";
        else
            cout << "B\n";
    }
}
