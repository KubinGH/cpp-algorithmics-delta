#include <bits/stdc++.h>

using namespace std;

const uint32_t MAX = (1u << 21) - 1;

struct node_t
{
    node_t *left, *right;
    uint32_t value;
    uint32_t tbegin, tend;
    node_t() : left(nullptr), right(nullptr), value(0),
               tbegin(0), tend(0) {}
    void set(uint32_t i, uint32_t v)
    {
        uint32_t mid = tbegin + (tend-tbegin)/2;
        if(i < tbegin or tend < i)
            ;
        else if(tbegin == tend and tbegin == i)
            value = v;
        else
        {
            if(tbegin <= i and i <= mid)
            {
                if(left == nullptr)
                {
                    left = new node_t;
                    left->tbegin = tbegin;
                    left->tend = mid;
                    left->value = left->tbegin;
                }
                left->set(i, v);
            }
            else if(mid+1 <= i and i <= tend)
            {
                if(right == nullptr)
                {
                    right = new node_t;
                    right->tbegin = mid+1;
                    right->tend = tend;
                    right->value = right->tbegin;
                }
                right->set(i, v);
            }
        }
        if(tbegin < tend)
            value = min(left == nullptr ? tbegin : left->value,
                        right == nullptr ? mid+1 : right->value);
    }
};

struct segment_tree
{
    node_t root;
    segment_tree()
    {
        root.value = 0;
        root.tbegin = 0; root.tend = MAX;
    }
    void set(uint32_t i, uint32_t v)
    {
        root.set(i, v);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t q;
    cin >> q;
    segment_tree tree;
    map<uint32_t, uint32_t> M;
    for(uint32_t i = 0; i < q; i++)
    {
        char c;
        cin >> c;
        uint32_t x;
        if(c == '+')
        {
            cin >> x;
            if(x <= MAX/2-8)
            {
                M[x]++;
                if(M[x] == 1)
                    tree.set(x, -1u);
            }
        }
        else if(c == '-')
        {
            cin >> x;
            if(x <= MAX/2-8)
            {
                M[x]--;
                if(M[x] == 0)
                {
                    tree.set(x, x);
                    M.erase(x);
                }
            }
        }
        else if(c == '?')
            cout << tree.root.value << "\n";
    }
}
