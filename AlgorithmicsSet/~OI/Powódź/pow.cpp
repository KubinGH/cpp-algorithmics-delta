#include <bits/stdc++.h>

using namespace std;

typedef pair<uint32_t, uint32_t> pair_u32;

const size_t MAX = 500000;
const uint32_t LIM = 1000000007;

struct disjoint_set
{
    array<uint32_t, MAX> parent, nrank, uheight;
    array<uint64_t, MAX> subresult;
    disjoint_set(uint32_t init = MAX)
    {
        for(uint32_t i = 0; i < init; i++)
            parent[i] = i, subresult[i] = 1;
    }
    uint32_t find_root(uint32_t node)
    {
        if(parent[node] == node)
            return parent[node];
        parent[node] = find_root(parent[node]);
        return parent[node];
    }
    bool unite(uint32_t first_node, uint32_t second_node, uint32_t cheight)
    {
        uint32_t first = find_root(first_node),
                 second = find_root(second_node), root;
        if(first == second)
            return false;
        if(nrank[second] > nrank[first])
        {
            nrank[second]++;
            parent[first] = second;
            root = second;
        }
        else
        {
            nrank[first]++;
            parent[second] = first;
            root = first;
        }
        subresult[root] = (((subresult[first] + cheight - uheight[first]) % LIM) * ((subresult[second] + cheight - uheight[second])) % LIM) % LIM;
        uheight[root] = cheight;
        return true;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t height, width, max_height;
    cin >> height >> width >> max_height;
    map<uint32_t, vector<pair_u32> > dams;
    for(uint32_t y = 0; y < height; y++) for(uint32_t x = 0; x < width - 1; x++)
    {
        uint32_t h;
        cin >> h;
        dams[h].emplace_back(y*width + x, y*width + x + 1);
    }
    for(uint32_t y = 0; y < height - 1; y++) for(uint32_t x = 0; x < width; x++)
    {
        uint32_t h;
        cin >> h;
        dams[h].emplace_back(y*width + x, (y+1)*width + x);
    }
    static disjoint_set dset(width * height);
    for(pair<uint32_t, vector<pair_u32> > mpair : dams)
    {
        uint32_t cheight = mpair.first;
        vector<pair_u32>& cdams = mpair.second;
        for(pair_u32 p : cdams)
            dset.unite(p.first, p.second, cheight);
    }
    uint32_t root = dset.find_root(0);
    cout << (dset.subresult[root] + max_height - dset.uheight[root]) % LIM;
}
