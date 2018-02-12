#include <bits/stdc++.h>
#define MAX 1048577
#define LEAF_FIX 524288

using namespace std;

uint32_t gcd(uint32_t a, uint32_t b)
{
    if(a == 0) return b;
    if(b == 0) return a;
    uint32_t t;
    while(b != 0)
    {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}

void set_value(array<uint32_t, MAX>& tree, uint32_t i, uint32_t value)
{
    tree[i] = value;
    while(i > 1)
    {
        i /= 2;
        tree[i] = gcd(tree[2*i], tree[2*i+1]);
    }
}

int main()
{
    uint32_t operations;
    cin >> operations;
    static array<uint32_t, MAX> tree;
    static array<list<uint32_t>, MAX> available;
    for(uint32_t i = 0; i < MAX; i++)
        available[0].push_back(LEAF_FIX + i);
    for(uint32_t o = 0; o < operations; o++)
    {
        int32_t temp;
        cin >> temp;
        uint32_t current = temp > 0 ? temp : -temp;
        if(temp > 0)
        {
            uint32_t index = available[0].front();
            available[0].pop_front();
            available[current].push_back(index);
            set_value(tree, index, current);
        }
        else
        {
            uint32_t index = available[current].front();
            available[current].pop_front();
            available[0].push_back(index);
            set_value(tree, index, 0);
        }
        cout << tree[1] << endl;
    }
}
