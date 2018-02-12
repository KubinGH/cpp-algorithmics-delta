#include <iostream>
#define abs_diff(a, b) ((a) < (b) ? (b) - (a) : (a) - (b))
#define MAX 100000

using namespace std;

typedef unsigned int uint32_t;

struct disjoint_set
{
    uint32_t parent_of[MAX], rank_of[MAX];
    disjoint_set(uint32_t n = MAX)
    {
        for(uint32_t i = 0; i < n; i++)
        {
            parent_of[i] = i;
        }
        fill(rank_of, rank_of + MAX, 0);
    }
    void unite(uint32_t first_node, uint32_t second_node)
    {
        uint32_t first = find_root(first_node);
        uint32_t second = find_root(second_node);
        if(rank_of[second] > rank_of[first])
        {
            parent_of[first] = second;
            rank_of[second]++;
        }
        else
        {
            parent_of[second] = first;
            rank_of[first]++;
        }
    }
    uint32_t find_root(uint32_t node)
    {
        if(parent_of[node] == node)
            return node;
        parent_of[node] = find_root(parent_of[node]);
        return parent_of[node];
    }
};

int main()
{
    uint32_t n;
    cin >> n;
    static uint32_t X[MAX];
    for(uint32_t i = 0; i < n; i++)
        cin >> X[i];
    static disjoint_set dset(n);
    for(uint32_t i = 0; i < n; i++)
    {
        if(X[i] <= i)
            dset.unite(i, i - X[i]);
        if(i + X[i] < n)
            dset.unite(i, i + X[i]);
    }
    uint32_t q;
    cin >> q;
    for(uint32_t i = 0; i < q; i++)
    {
        uint32_t a, b;
        cin >> a >> b; a--; b--;
        cout << (dset.find_root(a) == dset.find_root(b) ? "TAK" : "NIE") << endl;
    }
}
