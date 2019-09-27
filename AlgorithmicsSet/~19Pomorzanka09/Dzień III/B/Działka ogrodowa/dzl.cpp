#include <bits/stdc++.h>
#include <ktl/structures/segment_tree.cpp>

using namespace std;

const size_t RANGE = 1e5, FIX = 50000;

struct pulladd
{
    void operator() (size_t i, size_t nodeL, size_t nodeR, vector<int>& values, vector<int>& mutate)
    {
        if(nodeL < nodeR)
        {
            mutate[2*i] += mutate[i];
            mutate[2*i+1] += mutate[i];
        }
        values[i] += mutate[i];
        mutate[i] = 0;
    }
};

struct maxftor
{
    int operator() (int a, int b)
    {
        return max(a, b);
    }
};
int identity_element(maxftor) { return 0; }
int identity_element(pulladd) { return 0; }

using add_tree = segment_tree_i<
    int, maxftor, int, pulladd, plus<int>
>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    size_t w, h, n;
    cin >> w >> h >> n;

    static vector<tuple<size_t, size_t, int>> modify[RANGE];
    for(size_t i = 0; i < n; i++)
    {
        size_t x, y;
        cin >> x >> y;
        x += FIX;
        y += FIX;
        modify[x].emplace_back(y, y+h, 1);
        modify[x+w+1].emplace_back(y, y+h, -1);
    }

    add_tree tree(RANGE);

    int result = 0;
    for(size_t x = 0; x < RANGE; x++)
    {
        for(auto q : modify[x])
            tree.mut(get<0>(q), get<1>(q), get<2>(q));
        result = max(result, tree.get(0, RANGE - 1));
    }

    cout << result;
}
