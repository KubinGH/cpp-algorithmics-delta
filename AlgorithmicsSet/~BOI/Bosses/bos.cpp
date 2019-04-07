#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;

    vector<vector<uint32_t>> allows(n);
    for(uint32_t u = 0; u < n; u++)
    {
        uint32_t k;
        cin >> k;
        for(uint32_t j = 0; j < k; j++)
        {
            uint32_t v;
            cin >> v; v--;
            allows[v].push_back(u);
        }
    }

    uint32_t result = -1u - n;
    vector<bool> is_placed(n);
    vector<uint32_t> depth(n);
    for(uint32_t root = 0; root < n; root++)
    {
        fill(is_placed.begin(), is_placed.end(), false);
        fill(depth.begin(), depth.end(), -1u);
        queue<uint32_t> Q;

        uint32_t curr = 0;

        auto push = [&](uint32_t u) {
            is_placed[u] = true;
            curr += depth[u];
            for(uint32_t v : allows[u])
                if(not is_placed[v] and depth[u] + 1 < depth[v])
                    depth[v] = depth[u] + 1, Q.push(v);
        };

        depth[root] = 0;
        push(root);
        //cout << "$ " << root+1 << endl;
        for(uint32_t i = 1; i < n; i++)
        {
            if(Q.empty())
            {
                curr = result;
                break;
            }
            auto u = Q.front(); Q.pop();
            if(is_placed[u])
            {
                i--;
                continue;
            }
            push(u);
        }

        result = min(result, curr);
    }
    cout << result + n;
}
