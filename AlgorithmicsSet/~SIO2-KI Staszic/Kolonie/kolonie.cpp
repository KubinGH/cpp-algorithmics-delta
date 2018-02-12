#include <iostream>
#define MAX 1000000
#define MINF(a, b) ((a) < (b) ? (a) : (b))
#define MAXF(a, b) ((a) > (b) ? (a) : (b))

using namespace std;

struct disjoint_set
{
    uint32_t parent_of[MAX], rank_of[MAX];
    uint32_t total_mass[MAX];
    struct {
        int16_t minimum, maximum;
    } iq[MAX];
    disjoint_set(uint32_t n = MAX)
    {
        for(uint32_t i = 0; i < n; i++)
            parent_of[i] = i;
        fill(rank_of, rank_of + MAX, 0);
    }
    void unite(uint32_t first_node, uint32_t second_node)
    {
        uint32_t first = find_root(first_node);
        uint32_t second = find_root(second_node);
        if(first == second) return;
        if(rank_of[second] > rank_of[first])
            set_parent(first, second);
        else
            set_parent(second, first);
    }
    void set_parent(uint32_t child, uint32_t parent)
    {
        parent_of[child] = parent;
        rank_of[parent]++;
        total_mass[parent] += total_mass[child];
        iq[parent].minimum = MINF(iq[parent].minimum, iq[child].minimum);
        iq[parent].maximum = MAXF(iq[parent].maximum, iq[child].maximum);
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
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static disjoint_set dset(n);
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t mass;
        int16_t iq;
        cin >> mass >> iq;
        dset.total_mass[i] = mass;
        dset.iq[i].minimum = dset.iq[i].maximum = iq;
    }
    string command;
    while(cin >> command)
    {
        uint32_t a, b;
        if(command == "JOIN")
        {
            cin >> a >> b; a--; b--;
            dset.unite(a, b);
        }
        else if(command == "IQ_MIN")
        {
            cin >> a; a--;
            cout << dset.iq[dset.find_root(a)].minimum << '\n';
        }
        else if(command == "IQ_MAX")
        {
            cin >> a; a--;
            cout << dset.iq[dset.find_root(a)].maximum << '\n';
        }
        else if(command == "MASA")
        {
            cin >> a; a--;
            cout << dset.total_mass[dset.find_root(a)] << '\n';
        }
    }
}
