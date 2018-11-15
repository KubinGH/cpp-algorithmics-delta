#include <bits/stdc++.h>

using namespace std;

struct node
{
    node* child[2] = {nullptr, nullptr};
    uint32_t value = 0;
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<uint32_t> A(n), K(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    for(uint32_t i = 0; i < n; i++)
        cin >> K[i];
    node root;
    for(uint32_t i = 0; i < n; i++)
    {
        node* curr = &root; root.value++;
        for(uint32_t b = 32; b --> 0; )
        {
            for(uint32_t c = 0; c < 2; c++)
                if(curr->child[c] == nullptr)
                    curr->child[c] = new node;
            curr = curr->child[(K[i] & (1u << b)) >> b];
            curr->value++;
        }
    }
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t o = 0;
        node* curr = &root; root.value--;
        for(uint32_t b = 32; b --> 0; )
        {
            uint32_t p = (A[i] & (1u << b)) >> b;
            if(not curr->child[p]->value)
                p ^= 1;
            o |= (p << b);
            curr = curr->child[p];
            curr->value--;
        }
        cout << (A[i] ^ o) << " ";
    }
}
