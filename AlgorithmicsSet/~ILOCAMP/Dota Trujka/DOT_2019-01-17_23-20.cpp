#include <bits/stdc++.h>

using namespace std;

const uint32_t END = 1u << 31;

using graph_t = vector<vector<uint32_t>>;

void dfs_history(const graph_t& G, uint32_t u, vector<uint32_t>& H)
{
    H.push_back(u);
    for(uint32_t v : G[u])
        dfs_history(G, v, H);
    H.push_back(u | END);
}

struct blocks_manager
{
    vector<vector<uint32_t>> blocks, counters;
    vector<uint32_t> offset, in_block[2];
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, p;
    cin >> n >> p;

    vector<uint32_t> T(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> T[i];

    graph_t children(n);
    vector<uint32_t> parent(n);

    for(uint32_t i = 1; i < n; i++)
    {
        uint32_t j;
        cin >> j; j--;
        children[j].push_back(i);
        parent[i] = j;
    }

    const uint32_t b = ceil(sqrt(n));

    auto rebuild_blocks = [&]() {
        vector<uint32_t> H;
        dfs_history(children, 0, H);
        vector<vector<uint32_t>> B;
        B.emplace_back();
        for(uint32_t x : H)
        {
            if(B.back().size() >= b)
                B.emplace_back();
            B.back().push_back(x);
        }
        blocks_manager R;
        R.blocks = B;
        R.offset.resize(R.blocks.size());
        R.counters.resize(R.blocks.size(), vector<uint32_t>(p));
        R.in_block[0].resize(n); R.in_block[1].resize(n);
        for(uint32_t i = 0; i < R.blocks.size(); i++)
        {
            for(uint32_t u : R.blocks[i])
            {
                if(not (u & END))
                {
                    R.counters[i][T[u]]++;
                    R.in_block[0][u] = i;
                }
                else
                {
                    R.in_block[1][u ^ END] = i;
                }
            }
        }
        return R;
    };
    auto rebuild_graph_ip = [&](const blocks_manager& M) {
        for(uint32_t i = 0; i < n; i++)
            children[i].clear();
        vector<uint32_t> A;
        for(auto block : M.blocks)
            for(auto u : block)
                A.push_back(u);
        stack<uint32_t> V;
        uint32_t o = 0;
        for(uint32_t i = 0; i < M.blocks.size(); i++)
        {
            for(uint32_t u : M.blocks[i])
            {
                if(not (u & END))
                {
                    T[u] += M.offset[i]; T[u] %= p;
                    V.push(u);
                }
                else
                {
                    u ^= END;
                    V.pop();
                    if(not V.empty())
                    {
                        children[V.top()].push_back(u);
                        parent[u] = V.top();
                    }
                }
            }
        }
    };

    auto find_in_block = [&](uint32_t v, const vector<uint32_t>& block) {
        return find(block.begin(), block.end(), v) - block.begin();
    };
    auto count_type_in_block = [&](uint32_t a, uint32_t L, uint32_t R, const vector<uint32_t>& block) {
        uint32_t result = 0;
        for(uint32_t i = L; i < R; i++)
            if(not (block[i] & END) and T[block[i]] == a)
                result++;
        return result;
    };
    auto increment_type_in_block = [&](uint32_t a, uint32_t L, uint32_t R, const vector<uint32_t>& block, vector<uint32_t>& T1, vector<uint32_t>& counters) {
        for(uint32_t i = L; i < R; i++)
        {
            if(not (block[i] & END))
            {
                counters[T1[block[i]]]--;
                counters[T1[block[i]] = (T1[block[i]] + a) % p]++;
            }
        }
    };

    blocks_manager M = rebuild_blocks();

    uint32_t q;
    cin >> q;
    for(uint32_t qi = 0; qi < q; qi++)
    {
        if(qi % (4*b) == 0)
        {
            rebuild_graph_ip(M);
            M = rebuild_blocks();
        }
        uint32_t t;
        cin >> t;
        if(t == 1)
        {
            uint32_t v, a;
            cin >> v >> a; v--;
            uint32_t r = 0;
            if(M.in_block[0][v] == M.in_block[1][v])
            {
                uint32_t i = M.in_block[0][v];
                r += count_type_in_block((p + a - M.offset[i]) % p, find_in_block(v, M.blocks[i]), find_in_block(v | END, M.blocks[i])+1, M.blocks[i]);
            }
            else
            {
                uint32_t L = M.in_block[0][v], R = M.in_block[1][v];
                r += count_type_in_block((p + a - M.offset[L]) % p, find_in_block(v, M.blocks[L]), M.blocks[L].size(), M.blocks[L]);
                for(uint32_t i = L+1; i < R; i++)
                    r += M.counters[i][(p + a - M.offset[i]) % p];
                r += count_type_in_block((p + a - M.offset[R]) % p, 0, find_in_block(v | END, M.blocks[R]), M.blocks[R]);
            }
            cout << r << "\n";
        }
        else if(t == 2)
        {
            uint32_t v, a;
            cin >> v >> a; v--;
            if(M.in_block[0][v] == M.in_block[1][v])
            {
                uint32_t i = M.in_block[0][v];
                increment_type_in_block(a, find_in_block(v, M.blocks[i]), find_in_block(v | END, M.blocks[i])+1, M.blocks[i], T, M.counters[i]);
            }
            else
            {
                uint32_t L = M.in_block[0][v], R = M.in_block[1][v];
                increment_type_in_block(a, find_in_block(v, M.blocks[L]), M.blocks[L].size(), M.blocks[L], T, M.counters[L]);
                for(uint32_t i = L+1; i < R; i++)
                    M.offset[i] = (M.offset[i] + a) % p;
                increment_type_in_block(a, 0, find_in_block(v | END, M.blocks[R]), M.blocks[R], T, M.counters[R]);
            }
        }
        else if(t == 3)
        {
            uint32_t u, v;
            cin >> u >> v; u--; v--;
            abort();
        }
    }
}
