#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<uint> A(n);
    for(auto& a : A)
        cin >> a;

    const size_t m = *max_element(A.begin(), A.end()) + 1;

    vector<size_t> cnt(m);
    for(auto a : A)
        cnt[a]++;

    for(size_t d = m; d --> 1; )
    {
        uint c = 0;
        for(size_t x = d; x < m; x += d)
            c += cnt[x];
        if(c >= 2)
        {
            cout << d << endl;
            break;
        }
    }

}
