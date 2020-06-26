#include <bits/stdc++.h>

using namespace std;

vector<uint64_t> vertex_hash;
unordered_map<uint64_t, size_t> hash_count;
size_t result;
mt19937_64 gen;

void update_hash(size_t v, uint64_t x)
{
    result -= 2 * --hash_count[vertex_hash[v]];
    vertex_hash[v] ^= x;
    result += 2 * hash_count[vertex_hash[v]]++;
}

struct disjoint_set
{
    vector<size_t> repr;
    vector<vector<size_t>> members;
    vector<uint64_t> hash_mark;

    disjoint_set(size_t n) : repr(n), members(n), hash_mark(n)
    {
        for(size_t i = 0; i < n; i++)
        {
            repr[i] = i;
            members[i].push_back(i);
            update_hash(i, hash_mark[i] = gen());
        }
    }

    void unite(size_t u, size_t v)
    {
        if((u = repr[u]) == (v = repr[v]))
            return;
        if(members[u].size() > members[v].size())
            swap(u, v);
        for(auto w : members[u])
        {
            repr[w] = v;
            members[v].push_back(w);
            update_hash(w, hash_mark[u] ^ hash_mark[v]);
        }
        members[u].clear(); members[u].shrink_to_fit();
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t d, n, m;
    cin >> d >> n >> m;

    gen.seed(((d*n % size_t(1e9 + 7)) ^ m) ^ 0xAF8BED12);
    hash_count.reserve(4 * m);

    vertex_hash.resize(n);
    vector<disjoint_set> dset;
    for(size_t i = 0; i < d; i++)
        dset.emplace_back(n);
    hash_count[0] = 0;
    result = n;

    while(m --> 0)
    {
        size_t u, v, k;
        cin >> u >> v >> k; u--; v--; k--;
        dset[k].unite(u, v);
        cout << result << '\n';
    }
}
