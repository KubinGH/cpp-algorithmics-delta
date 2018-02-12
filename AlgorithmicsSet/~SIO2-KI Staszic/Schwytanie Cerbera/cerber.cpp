#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;
const size_t TSIZE = 2097152;
const size_t H_TSIZE = TSIZE/2;

struct bitter_tree
{
    array<uint32_t, TSIZE> values;
    bitter_tree(uint32_t init_nodes = MAX)
    {
        for(uint32_t i = 0; i < init_nodes; i++)
            push(i);
    }
    void push(uint32_t n)
    {
        n += H_TSIZE;
        if(values[n]) return;
        values[n]++;
        while(n > 1)
            values[n/=2]++;
    }
    void pop(uint32_t n)
    {
        n += H_TSIZE;
        if(not values[n]) return;
        values[n]--;
        while(n > 1)
            values[n/=2]--;
    }
    uint32_t find_nth(uint32_t n)
    {
        uint32_t node = 1, tbegin = 0, tend = TSIZE / 2 - 1;
        while(tbegin < tend)
        {
            if(values[node*2] < n)
            {
                n -= values[node*2];
                node *= 2; node++;
                tbegin = (tbegin+tend)/2 + 1;
            }
            else
            {
                node *= 2;
                tend = (tbegin+tend)/2;
            }
        }
        return tbegin + 1;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> A, B;
    for(uint32_t i = 0; i < n; i++)
        cin >> B[i];
    static bitter_tree tree(n);
    for(uint32_t i = n; i --> 0;)
    {
        A[i] = tree.find_nth(B[i]+1);
        tree.pop(A[i]-1);
    }
    for(uint32_t i = 0; i < n; i++)
        cout << A[i] << ' ';
}
