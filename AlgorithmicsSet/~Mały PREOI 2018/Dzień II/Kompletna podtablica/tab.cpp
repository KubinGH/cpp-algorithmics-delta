#include <bits/stdc++.h>

using namespace std;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k, q;
    cin >> n >> k >> q;
    uint32_t w = 1 << (31 - __builtin_clz(2*n-1));
    vector<uint32_t> A(w);
    using states_t = vector<pair<uint64_t, uint32_t>>;
    vector<states_t> states_pre(2*w), states_suf(2*w);
    vector<uint32_t> node_result(2*w), nodeL(2*w), nodeR(2*w);
    const uint64_t mask = ((1LLU << k) - 1) << 1;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];

    auto full = [&](uint64_t x) {
        return (x & mask) == mask;
    };
    auto merge_states = [&](states_t& O, const states_t& L, const states_t& R) {
        for(auto p : L)
            O.push_back(p);
        uint64_t s = O.back().first;
        for(auto p : R)
        {
            if(s != (p.first | s))
            {
                s |= p.first;
                O.emplace_back(s, p.second);
            }
        }
    };
    auto remake_node = [&](uint32_t v) {
        node_result[v] = -1u;
        states_pre[v].clear();
        states_suf[v].clear();
        if(v >= w)
        {
            states_pre[v].emplace_back(1LLU << A[v-w], v - w);
            states_suf[v].emplace_back(1LLU << A[v-w], v - w);
        }
        else
        {
            node_result[v] = min(node_result[2*v], node_result[2*v+1]);
            merge_states(states_pre[v], states_pre[2*v], states_pre[2*v+1]);
            merge_states(states_suf[v], states_suf[2*v+1], states_suf[2*v]);
            //reverse(states_suf[v].begin(), states_suf[v].end());
            uint32_t j_sav = 0;
            for(uint32_t i = states_suf[2*v].size(); i --> 0; )
            {
                uint32_t j;
                for(j = j_sav; j < states_pre[2*v+1].size(); j++)
                {
                    auto p1 = states_suf[2*v][i];
                    auto p2 = states_pre[2*v+1][j];
                    if(full(p1.first | p2.first))
                    {
                        node_result[v] = min(node_result[v], p2.second - p1.second + 1);
                        j_sav = j;
                        break;
                    }
                }
                if(j == states_pre[2*v+1].size())
                    break;
            }
        }
        //cout << v << ": " << bitset<8>(states_pre[v].back().first) << " " << nodeL[v] << " " << nodeR[v] << endl;
        if(full(states_pre[v].back().first))
            node_result[v] = min(node_result[v], nodeR[v] - nodeL[v] + 1);
    };
    for(uint32_t v = 2*w; v --> 1; )
    {
        if(v >= w)
            nodeL[v] = v-w, nodeR[v] = v-w;
        else
            nodeL[v] = nodeL[2*v], nodeR[v] = nodeR[2*v+1];
        states_pre[v].reserve(k); states_suf[v].reserve(k);
        remake_node(v);
    }
    while(q --> 0)
    {
        uint32_t t;
        cin >> t;
        if(t == 1)
        {
            uint32_t a, b;
            cin >> a >> b; a--;
            A[a] = b;
            uint32_t v = w+a;
            remake_node(v);
            while(v > 1)
                v /= 2, remake_node(v);
        }
        else if(t == 2)
            cout << int(node_result[1]) << "\n";
    }
}
