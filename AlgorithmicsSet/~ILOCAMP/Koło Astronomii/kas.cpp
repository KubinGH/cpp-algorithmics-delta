#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;

    if(k == 1 and n > 1) { cout << "-1"; return 0; }

    vector<pair<uint32_t, uint32_t>> E;



    for(auto p : E)
        if(p.first > p.second)
            swap(p.first, p.second);
    sort(E.begin(), E.end());


}
