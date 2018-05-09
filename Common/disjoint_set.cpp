using namespace std;

template<size_t N>
struct disjoint_set
{
    array<uint32_t, N> parent, nrank;
    disjoint_set(uint32_t init = N)
    {
        iota(parent.begin(), parent.begin() + init, 0);
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
            if(nrank[first] == nrank[second])
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
