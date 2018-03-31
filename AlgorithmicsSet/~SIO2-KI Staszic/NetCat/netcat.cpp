#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 200000;

struct disjoint_set
{
    array<uint32_t, MAX> parent, nrank;
    disjoint_set(uint32_t n)
    {
        iota(parent.begin(), parent.begin() + n, 0);
    }
    uint32_t find_root(uint32_t node)
    {
        if(node == parent[node])
            return node;
        parent[node] = find_root(parent[node]);
        return parent[node];
    }
    void unite(uint32_t first, uint32_t second)
    {
        first = find_root(first); second = find_root(second);
        if(nrank[second] > nrank[first])
        {
            parent[first] = second;
        }
        else
        {
            if(nrank[first] == nrank[second])
                nrank[first]++;
            parent[second] = first;
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    uint32_t free_id = 0;
    unordered_map<string, uint32_t> ids;
    static disjoint_set dset(2*n);
    for(uint32_t i = 0; i < n; i++)
    {
        string command, first, second;
        cin >> command >> first >> second;
        uint32_t first_id, second_id;
        first_id = ids.find(first) == ids.end() ? (ids[first] = free_id++) : ids[first];
        second_id = ids.find(second) == ids.end() ? (ids[second] = free_id++) : ids[second];
        if(command == "connect")
            dset.unite(first_id, second_id);
        else if(command == "sending")
            cout << (dset.find_root(first_id) == dset.find_root(second_id)
                     ? "Tak\n" : "Nie\n");
    }
}
