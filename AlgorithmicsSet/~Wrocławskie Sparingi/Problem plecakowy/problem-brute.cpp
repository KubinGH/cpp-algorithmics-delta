#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 7000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static array<pair<uint64_t, uint64_t>, MAX> A;
    map<uint64_t, uint64_t> M;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i].first >> A[i].second;
    sort(A.begin(), A.begin() + n);
    uint64_t r = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        if(A[i].first > m)
            break;
        for(uint32_t j = i+1; j < n; j++)
        {
            if(A[i].first + A[j].first > m)
                break;
            for(uint32_t k = j+1; k < n; k++)
            {
                if(A[i].first + A[j].first + A[k].first > m)
                    break;
                //cerr << i << " " << j << " " << k << " " << A[i].second + A[j].second + A[k].second << endl;
                r = max(r, A[i].second + A[j].second + A[k].second);
            }
            r = max(r, A[i].second + A[j].second);
        }
        r = max(r, A[i].second);
    }
    cout << r;
}
