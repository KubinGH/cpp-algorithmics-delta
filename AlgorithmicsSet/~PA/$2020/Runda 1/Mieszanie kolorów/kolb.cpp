#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<uint8_t> A(n);
    while(m --> 0)
    {
        size_t l, r, k;
        cin >> l >> r >> k; l--; r--; k--;
        for(size_t i = l; i <= r; i++)
            A[i] |= 1 << k;
    }

    size_t result = 0;
    for(auto& a : A)
        if(a == ((1 << 0) | (1 << 1)))
            result++;

    cout << result << endl;
}
