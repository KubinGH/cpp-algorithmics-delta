#include <bits/stdc++.h>

const size_t MAXE = 65536;
const size_t TSIZE = 2 * MAXE;

using namespace std;

void inc_value(array<uint32_t, TSIZE>& tree, uint32_t index)
{
    tree[index]++;
    while(index > 1)
    {
        index /= 2;
        tree[index]++;
    }
}

uint32_t find_best(array<uint32_t, TSIZE>& tree, uint32_t node,
                   uint32_t tbegin, uint32_t tend,
                   uint32_t sbegin, uint32_t send)
{
    if(send < tbegin or tend < sbegin) // disjoint
    {
        return 0;
    }
    else if(sbegin <= tbegin and tend <= send) // entire
    {
        return tree[node];
    }
    else // part
    {
        uint32_t left = find_best(tree, 2 * node, tbegin, (tbegin+tend)/2, sbegin, send);
        uint32_t right = find_best(tree, 2 * node + 1, (tbegin+tend)/2+1, tend, sbegin, send);
        return left + right;
    }
}

uint32_t find_best(array<uint32_t, TSIZE>& tree, uint32_t sbegin, uint32_t send)
{
    return find_best(tree, 1, 0, TSIZE/2 - 1, sbegin, send);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    uint16_t n;
    cin >> n;
    static array<uint32_t, TSIZE> tree;
    uint32_t result = 0;
    static map<int64_t, uint32_t> values;
    static array<int64_t, MAXE> oarr, arr;
    for(uint16_t i = 0; i < n; i++)
    {
        cin >> oarr[i];
        arr[i] = oarr[i];
    }
    sort(arr.begin(), arr.begin() + n);
    for(uint32_t i = 0; i < n; i++)
    {
        values[arr[i]] = i + 1;
    }
    for(uint16_t i = 0; i < n; i++)
    {
        uint32_t u = values[oarr[i]];
        inc_value(tree, MAXE + u);
        result += find_best(tree, u + 1, TSIZE / 2 - 1);
    }
    printf("%u", result);
}
