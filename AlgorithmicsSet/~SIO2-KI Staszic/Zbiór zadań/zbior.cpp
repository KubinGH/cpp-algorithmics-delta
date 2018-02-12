#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000;
const size_t TSIZE = 1 << 18;

typedef uint32_t(*tree_func)(uint32_t, uint32_t);

struct interval_tree
{
    array<uint32_t, TSIZE> values;
    uint32_t max_leaf = 1;
    void clear()
    {
        fill(values.begin(), values.end(), 0);
        max_leaf = 1;
    }
    void set_value(uint32_t node, uint32_t value)
    {
        values[node] = value;
        if(value > values[max_leaf]) max_leaf = node;
        while(node != 1)
            node /= 2, values[node] = max(values[node*2], values[node*2+1]);
    }
    uint32_t find_value(uint32_t node, uint32_t tbegin, uint32_t tend, uint32_t sbegin, uint32_t send)
    {
        if(tend < sbegin or send < tbegin)
            return 0;
        else if(sbegin <= tbegin and tend <= send)
            return values[node];
        else
            return max(find_value(node*2, tbegin, (tbegin+tend)/2, sbegin, send),
                       find_value(node*2+1, (tbegin+tend)/2+1, tend, sbegin, send));
    }
    uint32_t find_value(uint32_t sbegin, uint32_t send)
    {
        return find_value(1, 0, TSIZE/2-1, sbegin, send);
    }
};

uint32_t max(uint32_t a, uint32_t b)
{
    return a > b ? a : b;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint16_t m;
    cin >> m;
    static array<interval_tree, 10> tree;
    for(uint16_t mi = 0; mi < m; mi++)
    {
        uint32_t n;
        cin >> n;
        static array<int32_t, MAX> A, B;
        static array<pair<int32_t, uint32_t>, MAX> S;
        for(uint32_t i = 0; i < n; i++)
            cin >> A[i], S[i].first = A[i], S[i].second = i;
        sort(S.begin(), S.begin()+n);
        for(uint32_t i = 0; i < n; i++)
            B[S[i].second] = i == 0 or S[i-1].first != S[i].first ? i : B[S[i-1].second];
        for(uint32_t i = 0; i < n; i++)
        {
            uint32_t v = max(1, B[i] > 0 ? tree[mi].find_value(0, B[i]-1) + 1 : 0);
            tree[mi].set_value(TSIZE/2+B[i], v);
        }
        cout << tree[mi].values[tree[mi].max_leaf] << '\n';
    }
}
