#include <bits/stdc++.h>
#define MAX 1000000

using namespace std;

typedef unsigned int uint32_t;

struct disjoint_set_t
{
    uint32_t *parent_of, *rank_of;
    void init(uint32_t* mem_parent_of, uint32_t* mem_rank_of)
    {
        parent_of = mem_parent_of; rank_of = mem_rank_of;
        for(uint32_t i = 0; i < MAX; i++)
        {
            parent_of[i] = i; rank_of[i] = 0;
        }
    }
    uint32_t find_root(uint32_t node)
    {
        if(parent_of[node] == node)
            return node;
        else
        {
            parent_of[node] = find_root(parent_of[node]);
            return parent_of[node];
        }
    }
    void union_trees(uint32_t node_x, uint32_t node_y)
    {
        uint32_t root_x = find_root(node_x), root_y = find_root(node_y);
        if(rank_of[root_x] > rank_of[root_y])
            parent_of[root_y] = root_x;
        else if(rank_of[root_x] < rank_of[root_y])
            parent_of[root_x] = root_y;
        else
        {
            rank_of[root_x]++;
            parent_of[root_y] = root_x;
        }
    }
} disjoint_set;

int main()
{
    uint32_t people, pairs;
    scanf("%u %u", &people, &pairs);
    static uint32_t mem_parent_of[MAX], mem_rank_of[MAX];
    disjoint_set.init(mem_parent_of, mem_rank_of);
    for(uint32_t i = 0; i < pairs; i++)
    {
        uint32_t x, y;
        scanf("%u %u", &x, &y); x--; y--;
        disjoint_set.union_trees(x, y);
    }
    uint32_t result = 0;
    static bool found_root[MAX];
    for(uint32_t i = 0; i < people; i++)
    {
        uint32_t root = disjoint_set.find_root(i);
        if(not found_root[root])
        {
            found_root[root] = true;
            result++;
        }
    }
    printf("%u", result);
}
