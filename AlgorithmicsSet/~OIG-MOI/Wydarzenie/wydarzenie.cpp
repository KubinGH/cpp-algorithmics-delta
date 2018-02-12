#include <bits/stdc++.h>
#define MAX 1000001

using namespace std;

typedef unsigned int uint32_t;

struct disjoint_set
{
    uint32_t rank_of[MAX], parent_of[MAX];
    disjoint_set(uint32_t init = MAX)
    {
        for(uint32_t i = 0; i < init; i++)
        {
            parent_of[i] = i;
            rank_of[i] = 0;
        }
    }

    uint32_t find_root(uint32_t node)
    {
        if(parent_of[node] == node)
            return node;
        parent_of[node] = find_root(parent_of[node]);
        return parent_of[node];
    }

    void unite(uint32_t first_n, uint32_t second_n)
    {
        uint32_t first = find_root(first_n), second = find_root(second_n);
        if(rank_of[second] > rank_of[first])
        {
            rank_of[second]++;
            parent_of[first] = second;
        }
        else
        {
            rank_of[first]++;
            parent_of[second] = first;
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    uint32_t n;
    cin >> n;
    static disjoint_set dset;
    for(uint32_t i = 1; i < n + 1; i++)
    {
        uint32_t o;
        cin >> o;
        if(o != 0)
            dset.unite(i, o);
    }
    uint32_t k;
    cin >> k;
    static bool heard[MAX];
    uint32_t result = 0;
    for(uint32_t i = 0; i < k; i++)
    {
        uint32_t c;
        cin >> c;
        uint32_t root = dset.find_root(c);
        if(not heard[root])
        {
            result++;
            heard[root] = true;
        }
    }
    cout << result;
}
