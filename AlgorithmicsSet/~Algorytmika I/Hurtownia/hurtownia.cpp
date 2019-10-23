#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 250000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint64_t, MAX> A;
    static array<uint64_t, MAX+1> S;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i], S[i+1] = S[i] + A[i];
    set<pair<uint64_t, uint32_t>> R;
    uint64_t s = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        uint64_t b;
        cin >> b;
        if(s + b <= S[i+1])
        {
            R.emplace(b, i);
            s += b;
        }
        else if(not R.empty() and b < R.rbegin()->first)
        {
            s -= R.rbegin()->first;
            R.erase(*R.rbegin());
            R.emplace(b, i);
            s += b;
        }
    }
    vector<uint32_t> result;
    for(pair<uint64_t, uint32_t> p : R)
        result.push_back(p.second + 1);
    sort(result.begin(), result.end());
    cout << R.size() << '\n';
    for(uint32_t i : result)
        cout << i << " ";
}
