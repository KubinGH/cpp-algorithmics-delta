#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, l, p;
    cin >> n >> l >> p;
    uint32_t m = l + p;
    stack<int32_t> buffer;
    int32_t ls = 0, rs = 0;
    //unordered_map<int32_t, uint32_t> req; req.reserve(1e5);
    static uint32_t M_req[size_t(1e6)];
    fill(M_req, M_req + size_t(1e6), 1e9);
    uint32_t* req = M_req + size_t(5e5);
    req[0] = 0;
    vector<pair<int32_t, uint32_t>> to_add;
    for(uint32_t i = 0; i < m; i++)
    {
        vector<int32_t> cmoves;
        for(uint32_t j = 0; j < n; j++)
        {
            int32_t w;
            cin >> w;
            if(i >= l)
                rs += w, w *= -1;
            else
                ls += w;
            buffer.push(w);
        }
        cmoves.push_back(buffer.top()); buffer.pop();
        while(not buffer.empty())
            cmoves.push_back(cmoves.back() + buffer.top()), buffer.pop();
        for(pair<int32_t, uint32_t> c : req)
        {
            for(uint32_t i = 0; i < cmoves.size(); i++)
            {
                int32_t k = c.first + cmoves[i];
                uint32_t v = c.second + i + 1;
                if(v < req[k])
                    to_add.emplace_back(k, v);
            }
        }
        for(pair<int32_t, uint32_t> p : to_add)
        {
            int32_t k; uint32_t v;
            tie(k, v) = p;
            if(req[k] > v)
                req[k] = v;
        }
    }
    cout << req[ls - rs];
}
