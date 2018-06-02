#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t a, b, c, d;
    while(cin >> a >> b >> c >> d)
    {
        if(a == 0) break;
        vector<pair<uint64_t, uint64_t>> V, W;
        V.emplace_back(a, b);
        W.emplace_back(c, d);
        while(a)
        {
            V.emplace_back(b%a, a);
            tie(a, b) = V.back();
        }
        while(c)
        {
            W.emplace_back(d%c, c);
            tie(c, d) = W.back();
        }
        //for(auto p : V)
        //    cout << "<" << p.first << " " << p.second << "> "; cout << endl;
        reverse(W.begin(), W.end());
        //for(auto p : W)
        //    cout << "<" << p.first << " " << p.second << "> "; cout << endl;
        uint32_t i, j;
        for(i = 0; i < V.size(); i++)
        {
            bool f = false;
            for(j = 0; j < W.size() and not f; j++)
            {
                if(V[i] == W[j])
                    f = true;
            }
            if(f)
                break;
        }
        if(i == V.size())
            cout << "NIE\n";
        else
        {
            cout << "TAK\n";
            for(uint32_t t = 0; t <= i; t++)
                cout << V[t].first << " " << V[t].second << " ";
            for(uint32_t t = j; t < W.size(); t++)
                cout << W[t].first << " " << W[t].second << " ";
            cout << "\n";
        }
        cout.flush();
    }
}
