#include <bits/stdc++.h>
#define FMT(n) (n == nullptr ? -1 : (int)n->i)

using namespace std;

const size_t MAX = 500000;

struct node_t { node_t* left, *right; uint32_t i; };

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<node_t, MAX> nodes;
    nodes[0].i = 1;
    nodes[0].left = nullptr;
    nodes[0].right = &nodes[1];
    for(uint32_t i = 1; i < n - 1; i++)
    {
        nodes[i].i = i + 1;
        nodes[i].left = &nodes[i - 1];
        nodes[i].right = &nodes[i + 1];
    }
    nodes[n-1].i = n;
    nodes[n-1].left = &nodes[n-2];
    nodes[n-1].right = nullptr;
    for(uint32_t t = 0; t < n; t++)
    {
        uint32_t c; cin >> c; c--;
        cout << FMT(nodes[c].left) << " " << FMT(nodes[c].right) << "\n";
        if(nodes[c].left != nullptr) nodes[c].left->right = nodes[c].right;
        if(nodes[c].right != nullptr) nodes[c].right->left = nodes[c].left;
    }

}
