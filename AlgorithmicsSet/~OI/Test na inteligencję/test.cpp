#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 20;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static vector<uint32_t> A[MAX];
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a;
        cin >> a;
        A[a].push_back(i);
    }
    uint32_t q;
    cin >> q;
    while(q --> 0)
    {
        uint32_t m, i = 0;
        cin >> m;
        while(m --> 0)
        {
            uint32_t a;
            cin >> a;
            auto it = lower_bound(A[a].begin(), A[a].end(), i);
            i = it != A[a].end() ? *it+1 : ~0;
        }
        cout << (i <= n ? "TAK" : "NIE") << "\n";
    }
}
