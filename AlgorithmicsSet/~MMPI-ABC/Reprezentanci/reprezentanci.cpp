#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e5 + 1;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    bitset<MAX> exists;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a;
        cin >> a;
        exists[a] = true;
    }
    cout << exists.count() << '\n';
    for(uint32_t i = 0; i < MAX; i++)
        if(exists[i])
            cout << i << " ";
}
