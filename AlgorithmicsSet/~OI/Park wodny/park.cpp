#include <bits/stdc++.h>
#ifdef XHOVA
#define cdbg cerr
#else
#define cdbg if(0) cerr
#endif

using namespace std;

const size_t K = 10;

inline uint32_t coor_to_index(uint32_t x, uint32_t y) { return x + (y<<K); }
inline pair<uint32_t, uint32_t> index_to_coor(uint32_t c) { return {c&0x3FF, (c>>K)&0x3FF}; }

struct disjoint_set
{
    vector<uint32_t> parent, left, top, right, bottom, ncount;
    disjoint_set(uint32_t n)
    {
        parent.resize(n); iota(parent.begin(), parent.end(), 0);
        top.resize(n); left.resize(n); right.resize(n); bottom.resize(n);
        ncount.resize(n, 1);
        for(uint32_t i = 0; i < n; i++)
        {
            left[i] = right[i] = index_to_coor(i).first;
            top[i] = bottom[i] = index_to_coor(i).second;
        }
    }
    uint32_t root(uint32_t v) { return (v == parent[v]) ? v : (parent[v] = root(parent[v])); }
    void unite(uint32_t u, uint32_t v)
    {
        cdbg << "unite " << u << " " << v << endl;
        if((u = root(u)) == (v = root(v)))
            return;
        parent[v] = u;
        ncount[u] += ncount[v];
        left[u] = min(left[u], left[v]); right[u] = max(right[u], right[v]);
        top[u] = min(top[u], top[v]); bottom[u] = max(bottom[u], bottom[v]);
    }
};

template<typename Callback>
void for_each_neighbour(uint32_t x, uint32_t y, uint32_t w, uint32_t h, Callback func)
{
    if(x > 0) func(x - 1, y);
    if(x < w - 1) func(x + 1, y);
    if(y > 0) func(x, y - 1);
    if(y < h - 1) func(x, y + 1);
}

struct bittyset
{
    vector<bool> mark;
    vector<uint32_t> marks;
    bittyset(uint32_t n) { mark.resize(n); marks.reserve(n); }
    void insert(uint32_t i)
    {
        if(mark[i]) return;
        mark[i] = true;
        marks.push_back(i);
    }
    void clear()
    {
        for(uint32_t i : marks)
            mark[i] = false;
        marks.clear();
    }
    void pop_back()
    {
        mark[marks.back()] = false;
        marks.pop_back();
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static bool A[1024][1024];
    uint32_t free = 0;
    for(uint32_t y = 0; y < n; y++)
    {
        string row;
        cin >> row;
        for(uint32_t x = 0; x < n; x++)
        {
            A[x][y] = row[x] - 'A';
            if(not A[x][y]) free++;
        }
    }
    cdbg << "input done " << endl;
    disjoint_set dset(1<<(K<<1));
    for(uint32_t y = 0; y < n; y++)
      for(uint32_t x = 0; x < n; x++)
    {
        cdbg << x << " " << y << endl;
        if(A[x][y]) for_each_neighbour(x, y, n, n, [&](uint32_t cx, uint32_t cy) {
            if(A[cx][cy])
                dset.unite(coor_to_index(x, y), coor_to_index(cx, cy));
        });
    }
    cdbg << "dset done " << endl;
    bitset<1<<(K<<1)> rect_added;
    vector<tuple<uint32_t, uint32_t, uint32_t, uint32_t>> rects;
    rects.reserve(n*n);
    for(uint32_t y = 0; y < n; y++)
      for(uint32_t x = 0; x < n; x++)
    {
        uint32_t c = dset.root(coor_to_index(x, y));
        if(A[x][y] and not rect_added[c])
            rect_added[c] = true, rects.emplace_back(dset.left[c], dset.top[c], dset.right[c], dset.bottom[c]);
    }
    cdbg << "rects done " << endl;
    uint32_t r = min(free, 2u);
    bittyset used(1<<(K<<1)), possible(1<<(K<<1));
    for(auto t : rects)
    {
        uint32_t x1, y1, x2, y2; tie(x1, y1, x2, y2) = t;
        uint32_t a = coor_to_index(x1, y1);
        r = max(r, dset.ncount[dset.root(a)]);
        cdbg << x1 << " " << y1 << " . " << x2 << " " << y2 << endl;
        possible.clear();
        if(y1 > 0) for(uint32_t x = x1; x <= x2; x++)
            possible.insert(coor_to_index(x, y1-1));
        if(y2 < n - 1) for(uint32_t x = x1; x <= x2; x++)
            possible.insert(coor_to_index(x, y2+1));
        if(x1 > 0) for(uint32_t y = y1; y <= y2; y++)
            possible.insert(coor_to_index(x1-1, y));
        if(x2 < n - 1) for(uint32_t y = y1; y <= y2; y++)
            possible.insert(coor_to_index(x2+1, y));
        for(uint32_t i = 0; i < possible.marks.size(); i++)
        {
            uint32_t px, py; tie(px, py) = index_to_coor(possible.marks[i]);
            uint32_t z = possible.marks.size();
            for_each_neighbour(px, py, n, n, [&](uint32_t cx, uint32_t cy){
                if(not A[cx][cy])
                    possible.insert(coor_to_index(cx, cy));
            });
            uint32_t d = possible.marks.size() - z;
            for(uint32_t j = i; j < possible.marks.size(); j++)
            {
                tie(px, py) = index_to_coor(possible.marks[i]);
                used.insert(dset.root(a));
                for(uint32_t s = 0; s < 2; s++)
                {
                    if(not A[px][py])
                    {
                        for_each_neighbour(px, py, n, n, [&](uint32_t cx, uint32_t cy) {
                            if(A[cx][cy])
                                used.insert(dset.root(coor_to_index(cx, cy)));
                        });
                        used.insert(dset.root(coor_to_index(px, py)));
                    }
                    tie(px, py) = index_to_coor(possible.marks[j]);
                }
                uint32_t q = 0;
                for(uint32_t c : used.marks)
                    q += dset.ncount[dset.root(c)];
                r = max(r, q);
                used.clear();
            }
            for(uint32_t j = 0; j < d; j++)
                possible.pop_back();
        }
    }
    cout << r;
}
