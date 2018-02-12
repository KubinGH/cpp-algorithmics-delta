#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 200000;

struct disjoint_set
{
    array<int32_t, MAX> parent, nrank, result;
    int32_t result_value = -1;
    disjoint_set()
    {
        for(uint32_t i = 0; i < MAX; i++)
        {
            parent[i] = i;
        }
        fill(nrank.begin(), nrank.end(), 0);
        fill(result.begin(), result.end(), -2);
        nrank[0] = 2*MAX; result[0] = -1;
    }
    void unite(int32_t first_node, int32_t second_node)
    {
        int32_t first = find_root(first_node);
        int32_t second = find_root(second_node);
        if(first == second) return;
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
    int32_t find_root(int32_t node)
    {
        if(parent[node] == node)
            return node;
        int32_t result_find = find_result(node);
        parent[node] = find_root(parent[node]);
        if(parent[node] == 0 and result[node] == -2)
        {
            int32_t v;
            if(result_find < 0)
                v = result_value;
            else
                v = result_find;
            result[node] = v;
        }
        return parent[node];
    }
    int32_t find_result(int32_t node)
    {
        if(result[node] != -2 or parent[node] == node)
            return result[node];
        else
            return find_result(parent[node]);
    }
};

int main()
{
    uint32_t n, m;
    cin >> n >> m;
    static array<array<int32_t, 2>, MAX> parents_before, parents;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> parents[i][0] >> parents[i][1];
        if(parents[i][0] != -1) parents[i][0]--;
        if(parents[i][1] != -1) parents[i][1]--;
    }
    copy(parents.begin(), parents.begin() + n, parents_before.begin());
    static array<array<int32_t, 2>, 2*MAX> events;
    for(uint32_t i = 0; i < m; i++)
    {
        cin >> events[i][0] >> events[i][1]; events[i][0]--; events[i][1]--;
        parents[events[i][0]][events[i][1]] = -1;
    }
    static disjoint_set tree;
    for(uint32_t i = 0; i < n; i++)
    {
        if(parents[i][0] != -1)
            tree.unite(i, parents[i][0]);
        if(parents[i][1] != -1)
            tree.unite(i, parents[i][1]);
    }
    tree.result_value = -1;
    for(uint32_t i = 0; i < n; i++)
    {
        tree.find_root(i);
    }
    for(uint32_t i = m; i --> 0;)
    {
        tree.result_value = i;
        int32_t a = events[i][0], b = parents_before[events[i][0]][events[i][1]];
        tree.unite(a, b);
        tree.find_root(a);
        tree.find_root(b);
    }
    for(uint32_t i = 0; i < n; i++)
    {
        int32_t r = tree.find_result(i);
        cout << (r != -2 ? r : 0) << '\n';
    }
}
