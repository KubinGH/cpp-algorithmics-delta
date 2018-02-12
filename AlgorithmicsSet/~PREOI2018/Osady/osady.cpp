#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000;
const size_t JUMP_PTRS = 25;
const uint32_t INF = numeric_limits<uint32_t>::max();

struct village_t
{
    uint32_t index;
    string name;
};

unordered_map<string, uint32_t> village_idx;
array<village_t, MAX> villages;
array<uint32_t, MAX> distance_to_root, parent, depth;
array<array<uint32_t, JUMP_PTRS>, MAX> jump_pointers;
uint32_t village_count = 0;

void init(string name)
{
    villages[0].name = name;
    village_idx[name] = 0;
    distance_to_root[0] = 0; parent[0] = 0;
    village_count++;
    for(uint32_t i = 0; i < MAX; i++)
    {
        villages[i].index = i;
        for(uint32_t j = 0; j < JUMP_PTRS; j++)
            jump_pointers[i][j] = INF;
    }
}

void nowa_osada(string nowa, string stara, int dlugosc)
{
    villages[village_count].name = nowa;
    village_idx[nowa] = village_count;
    uint32_t old_idx = village_idx[stara];
    distance_to_root[village_count] = distance_to_root[old_idx] + dlugosc;
    parent[village_count] = old_idx;
    depth[village_count] = depth[old_idx] + 1;
    jump_pointers[village_count][0] = parent[village_count];
    for(uint32_t i = 1; i < JUMP_PTRS; i++)
    {
        uint32_t x = jump_pointers[village_count][i-1];
        jump_pointers[village_count][i] = (x != INF) ? jump_pointers[x][i-1] : x;
    }
    village_count++;
}


uint32_t LCA(uint32_t u, uint32_t v)
{
    if(depth[u] < depth[v])
        swap(u, v);
    for(uint32_t i = JUMP_PTRS; i --> 0;)
    {
        if(depth[u] >= (1u << i) and depth[u] - (1u << i) >= depth[v])
            u = jump_pointers[u][i];
    }
    if(u == v) return u;
    for(uint32_t i = JUMP_PTRS; i --> 0;)
    {
        if(jump_pointers[u][i] != jump_pointers[v][i] and jump_pointers[u][i] != INF)
        {
            u = jump_pointers[u][i];
            v = jump_pointers[v][i];
        }
    }
    return jump_pointers[u][0];
}

int odleglosc(string pierwsza, string druga)
{
    uint32_t first = village_idx[pierwsza], second = village_idx[druga];
    uint64_t r = distance_to_root[first] + distance_to_root[second] -
                 2 * distance_to_root[LCA(first, second)];
    return r;
}
