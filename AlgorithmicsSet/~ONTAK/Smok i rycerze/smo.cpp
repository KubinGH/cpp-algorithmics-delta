#include <bits/stdc++.h>

using namespace std;

struct line
{
    int A, B, C;
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t T;
    cin >> T;

    for(size_t t = 1; t <= T; t++)
    {
        size_t n, m;
        cin >> n >> m;

        size_t regions = 1;
        vector<line> L;

        for(size_t i = 0; i < n; i++)
        {
            line l;
            cin >> l.A >> l.B >> l.C;

            auto g = __gcd(__gcd(l.A, l.B), l.C);
            l.A /= g; l.B /= g; l.C /= g;

            bool covered = false;
            for(auto& k : L)
                if(l.A == k.A and l.B == k.B and l.C == k.C)
                    covered = true;
            if(covered)
                continue;

            regions++;
            for(auto& k : L)
                if(l.A*k.B != l.B*k.A)
                    regions++;

            L.push_back(l);
        }

        vector<pair<uint64_t, uint64_t>> ids(m);
        for(auto& id : ids)
        {
            int x, y;
            cin >> x >> y;
            for(size_t i = 0; i < n; i++)
            {
                if((int64_t)L[i].A*x + (int64_t)L[i].B*y + L[i].C >= 0)
                {
                    if(i < 64) id.first  |= (1ull << i);
                    else       id.second |= (1ull << (i - 64));
                }
            }
        }
        sort(ids.begin(), ids.end());
        ids.erase(unique(ids.begin(), ids.end()), ids.end());

        assert(ids.size() <= regions);
        cout << (ids.size() == regions ? "TAK" : "NIE") << endl;
    }
}
