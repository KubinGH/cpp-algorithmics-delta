#include <iostream>
#include <valarray>
#include <vector>

using namespace std;

struct segment_tree
{
    struct node
    {
        valarray<uint> dig;
        uint lazy_shift;
        node() : dig(10), lazy_shift(0) {}
    };
    size_t w;
    vector<node> nodes;

    template<typename It>
    segment_tree(It first, It last) : w(1 << __lg(2*(distance(first, last))-1)), nodes(2*w)
    {
        size_t i = 0;
        for(auto it = first; it != last; ++it, i++)
            nodes[w+i].dig[*it % 10] = 1;
        for(i = w; i --> 1; )
            nodes[i].dig = nodes[2*i].dig + nodes[2*i+1].dig;
    }

    void pull(size_t i, size_t L, size_t R)
    {
        valarray<uint> dig(10);
        for(size_t j = 0; j < 10; j++)
            dig[(j+nodes[i].lazy_shift)%10] = nodes[i].dig[j];
        nodes[i].dig = dig;

        if(L < R)
        {
            nodes[2*i].lazy_shift += nodes[i].lazy_shift;
            nodes[2*i+1].lazy_shift += nodes[i].lazy_shift;
        }
        nodes[i].lazy_shift = 0;
    }

    uint travel(size_t i, size_t nodeL, size_t nodeR, size_t L, size_t R, uint s)
    {
        pull(i, nodeL, nodeR);
        if(R < nodeL or nodeR < L)
            return 0;
        else if(L <= nodeL and nodeR <= R)
        {
            nodes[i].lazy_shift += s;
            pull(i, nodeL, nodeR);
            uint res = 0;
            for(size_t j = 0; j < 10; j++)
                res += nodes[i].dig[j] * j;
            return res;
        }
        else
        {
            auto res = travel(2*i, nodeL, (nodeL+nodeR)/2, L, R, s) + travel(2*i+1, (nodeL+nodeR)/2+1, nodeR, L, R, s);
            nodes[i].dig = nodes[2*i].dig + nodes[2*i+1].dig;
            return res;
        }
    }

    uint travel(size_t L, size_t R, uint s = 0) { return travel(1, 0, w-1, L, R, s % 10); }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    vector<uint> A(n);
    for(auto& a : A)
        cin >> a;

    segment_tree T(A.begin(), A.end());

    while(q --> 0)
    {
        char c;
        cin >> c;

        if(c == '+')
        {
            size_t i, j; uint v;
            cin >> i >> j >> v; i--; j--;
            T.travel(i, j, v);
        }
        else if(c == '?')
        {
            size_t i, j;
            cin >> i >> j; i--; j--;
            cout << T.travel(i, j) << '\n';
        }
    }
}
