#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 20;
const uint32_t COOR_BITS = 10;

uint32_t coor(uint32_t x, uint32_t y)
{
    return (x << COOR_BITS) + y;
}
uint32_t xvalue(uint32_t c)
{
    return c >> COOR_BITS;
}
uint32_t yvalue(uint32_t c)
{
    return c & ((1 << COOR_BITS) - 1);
}

struct disjoint_set
{
    array<uint32_t, MAX> parent, ncount;
    unordered_set<uint32_t> root_set;
    disjoint_set(uint32_t n)
    {
        for(uint32_t y = 0; y < n; y++)
        {
            for(uint32_t x = 0; x < n; x++)
            {
                uint32_t c = coor(x, y);
                parent[c] = c;
                ncount[c] = 1;
                root_set.insert(c);
            }
        }
        ncount[MAX-1] = 0;
    }
    uint32_t find_root(uint32_t node)
    {
        if(parent[node] == node)
            return node;
        parent[node] = find_root(parent[node]);
        return parent[node];
    }
    void unite(uint32_t first_node, uint32_t second_node)
    {
        uint32_t first = find_root(first_node), second = find_root(second_node);
        if(second > first)
        {
            parent[first] = second;
            ncount[second] += ncount[first];
            root_set.erase(first);
        }
        else
        {
            parent[second] = first;
            ncount[first] += ncount[second];
            root_set.erase(second);
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static disjoint_set dset(n);
    static array<bool, MAX> A;
    for(uint32_t y = 0; y < n; y++)
    {
        for(uint32_t x = 0; x < n; x++)
        {
            char c;
            cin >> c;
            A[coor(x, y)] = c == 'B';
        }
    }
    static array<uint32_t, MAX> R;
    if(A[0])
        R[0] = coor(1, 1);
    for(uint32_t x = 1; x < n; x++)
    {
        if(A[coor(x, 0)])
        {
            uint32_t p = R[coor(x-1, 0)];
            R[coor(x, 0)] = coor(xvalue(p) + 1, 1);
            if(A[coor(x-1, 0)])
                dset.unite(coor(x-1, 0), coor(x, 0));
        }
    }
    for(uint32_t y = 1; y < n; y++)
    {
        if(A[coor(0, y)])
        {
            uint32_t p = R[coor(0, y-1)];
            R[coor(0, y)] = coor(1, yvalue(p) + 1);
            if(A[coor(0, y-1)])
                dset.unite(coor(0, y-1), coor(0, y));
        }
    }
    for(uint32_t y = 1; y < n; y++)
    {
        for(uint32_t x = 1; x < n; x++)
        {
            if(A[coor(x, y)])
            {
                uint32_t px = xvalue(R[coor(x-1, y)]),
                         py = yvalue(R[coor(x, y-1)]);
                R[coor(x, y)] = coor(px ? px+1 : 1, py ? py+1 : 1);
                if(px)
                    dset.unite(coor(x-1, y), coor(x, y));
                else if(py)
                    dset.unite(coor(x, y-1), coor(x, y));
            }
        }
    }
    vector<pair<uint32_t, uint32_t>> rects;
    for(uint32_t y = 0; y < n; y++)
    {
        for(uint32_t x = 0; x < n; x++)
        {
            if((x < n-1 and A[coor(x+1, y)]) or (y < n-1 and A[coor(x, y+1)]))
                R[coor(x, y)] = 0;
            uint32_t r = R[coor(x, y)];
            if(r)
                rects.emplace_back(coor(x-xvalue(r)+1, y-yvalue(r)+1), coor(x, y));
        }
    }
    static array<vector<uint32_t>, MAX> G;
    for(uint32_t y = 0; y < n; y++)
    {
        for(uint32_t x = 0; x < n; x++)
        {
            uint32_t c = coor(x, y);
            if(x > 0)   G[c].push_back(coor(x-1, y))
            if(x > n-1) G[c].push_back(coor(x+1, y))
            if(y > 0)   G[c].push_back(coor(x, y-1))
            if(y < n-1) G[c].push_back(coor(x, y+1))
        }
    }
}
