#include <bits/stdc++.h>

#ifdef XHOVA
#define debug_assert assert
#else
#define debug_assert void
#endif

using namespace std;

const size_t Horizontal = 0, Vertical = 1;
struct tile
{
    tile* x[2][2];
};

struct board
{
    vector<tile*> e[2][2];

    template<size_t axis>
    pair<board, board> split(size_t p)
    {

    }

    template<size_t axis>
    void invert()
    {
        debug_assert(e[axis][0].size() == e[axis][1].size());
        const size_t n = e[axis][0].size();
        for(size_t i = 0; i < 2; i++)
            reverse(e[axis][i].begin(), e[axis][i].end());
    }

    template<size_t axis>
    board merge(board a, board b)
    {
        debug_assert(a.e[axis][1].size() == b.e[axis][0].size());
        const size_t n = e[axis][0].size();
    }
};

int main()
{

}
