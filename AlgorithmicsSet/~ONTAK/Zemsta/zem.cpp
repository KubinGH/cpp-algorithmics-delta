#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t t;
    cin >> t;

    vector<uint64_t> F = {0, 1};
    while(F.back() < (1ull << 62))
        F.push_back(F.end()[-1] + F.end()[-2]);

    vector<uint64_t> G = {0, 1, 2, 3, 4, 6};
    while(G.back() < (1ull << 62))
        G.push_back(G.end()[-1] + G.end()[-4]);

    while(t --> 0)
    {
        uint64_t n, k;
        cin >> n >> k;

        bool win;
        if(k == 1)
            win = n & (n-1);
        else if(k == 2)
            win = not binary_search(F.begin(), F.end(), n);
        else if(k == 3)
            win = not binary_search(G.begin(), G.end(), n);
        cout << (win ? 'C' : 'R') << '\n';
    }
}
