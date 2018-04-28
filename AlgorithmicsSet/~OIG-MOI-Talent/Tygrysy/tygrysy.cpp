#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<pair<uint32_t, uint32_t>, MAX> P;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t r, k;
        cin >> r >> k;
        P[i].first = r; P[i].second = r / k;
    }
    sort(P.begin(), P.begin() + n);
    static array<uint32_t, MAX> R, M;
    for(uint32_t i = 0; i < n; i++)
        R[i] = P[i].first, M[i] = P[i].second;
    uint32_t result = 0;
    for(uint32_t i = n; i --> 0;)
    {
        cerr << R[i] << ": " << M[i] << endl;
        i = upper_bound(R.begin(), R.begin() + i, M[i]) - R.begin();
        result++;
    }
    cout << result;
}
