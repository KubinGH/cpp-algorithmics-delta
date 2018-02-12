#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000;

struct disjoint_set
{
    array<uint32_t, MAX> parent, nrank;
    disjoint_set(uint32_t init = MAX)
    {
        for(uint32_t i = 0; i < init; i++)
            parent[i] = i;
    }
    void unite(uint32_t first_node, uint32_t second_node)
    {
        uint32_t first = find_root(first_node),
                 second = find_root(second_node);
        if(nrank[second] > nrank[first])
        {
            parent[first] = second;
            nrank[second]++;
        }
        else
        {
            parent[second] = first;
            nrank[first]++;
        }
    }
    uint32_t find_root(uint32_t node)
    {
        if(parent[node] == node)
            return node;
        parent[node] = find_root(parent[node]);
        return parent[node];
    }
};

int main()
{
    uint32_t height, width;
    cin >> height >> width;
    static array<uint32_t, MAX*MAX> A;
    static array<bool, MAX*MAX> B;
}
