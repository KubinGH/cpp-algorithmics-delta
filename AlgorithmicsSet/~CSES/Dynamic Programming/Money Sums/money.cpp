#include <bits/stdc++.h>

using namespace std;

const size_t M = 1 << 18;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    bitset<M> S = {};
    S[0] = 1;
    while(n --> 0)
    {
        size_t a;
        cin >> a;
        S |= S << a;
    }

    cout << S.count() - 1 << endl;
    for(size_t x = 1; x < S.size(); x++)
        if(S[x])
            cout << x << ' ';
    cout << endl;

}
