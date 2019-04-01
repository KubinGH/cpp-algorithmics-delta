#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    uint32_t n;
    cin >> n;

    vector<vector<uint32_t>> P(n, vector<uint32_t>(n));
    vector<vector<uint32_t>> E(n, vector<uint32_t>(n));
    for(uint32_t i = 0; i < n; i++)
    {
        for(uint32_t j = 0; j < n; j++)
            cin >> P[i][j], P[i][j]--;

        reverse(P[i].begin(), P[i].end());
        for(uint32_t j = 0; j < n; j++)
            E[i][P[i][j]] = j;
    }

    uint32_t p;
    cin >> p;

    if(p == 1)
    {
        vector<uint32_t> result;
        for(uint32_t i = 0; i < n; i++)
            if(P[i].back() == i)
                result.push_back(i);

        cout << result.size() << endl;
        for(uint32_t i : result)
            cout << i+1 << " ";
    }
    else if(p == 2)
    {
        vector<vector<uint32_t>> kills(n), killed_by(n);
        for(uint32_t i = 0; i < n; i++)
            for(uint32_t j = 0; j < n; j++)
                if(E[j][j] < E[j][i])
                    kills[i].push_back(j), killed_by[j].push_back(i);

        vector<uint32_t> result;
        for(uint32_t s = 0; s < n; s++)
        {
            vector<uint32_t> checks = kills[s];
            checks.push_back(s);

            bool overok = false;
            for(uint32_t z : checks)
            {
                bool ok = true;
                vector<bool> is_to_kill(n);
                vector<uint32_t> to_kill;
                for(uint32_t i = 0; i < n; i++)
                    if(E[z][s] < E[z][i])
                        is_to_kill[i] = true, to_kill.push_back(i);
                for(uint32_t i : to_kill)
                {
                    bool nokill = true;
                    for(uint32_t j : killed_by[i])
                    {
                        if(not is_to_kill[j])
                            { nokill = false; break; }
                    }
                    if(nokill)
                        { ok = false; break; }
                }
                if(ok) { overok = true; break; }
            }
            if(overok)
                result.push_back(s);
        }
        cout << result.size() << endl;
        for(uint32_t i : result)
            cout << i+1 << " ";
    }
}
