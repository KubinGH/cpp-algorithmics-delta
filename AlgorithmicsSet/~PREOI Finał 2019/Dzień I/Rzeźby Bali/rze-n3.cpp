#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, a, b;
    cin >> n >> a >> b;
    vector<uint64_t> Y(n), S(n + 1);
    for(uint32_t i = 0; i < n; i++)
        cin >> Y[i], S[i+1] = S[i] + Y[i];


}
