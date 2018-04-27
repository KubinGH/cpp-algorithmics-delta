#include <bits/stdc++.h>

using namespace std;

typedef long long int int64_t;
typedef unsigned long long int uint64_t;
typedef pair<int64_t, int64_t> pair_i64;

const size_t MAX = 100000, TSIZE = 1 << 16;
const int64_t MAX_COOR = 2*1073741824llu;

struct node_t
{
    node_t *left, *right;
    int64_t tbegin, tend;
    uint64_t value;
    node_t()
    {
        left = right = NULL;
        tbegin = tend = value = 0;
    }
    void set(int64_t x, uint64_t new_value)
    {
        //cout << "set " << x << " <- " << new_value << " @ " << tbegin << " " << tend << endl;
        if(tbegin == tend and tbegin == x)
        {
            value = max(value, new_value);
            return;
        }
        int64_t mid = (tbegin+tend)>>1;
        if(tbegin <= x and x <= mid)
        {
            if(left == NULL)
            {
                left = new node_t;
                left->tbegin = tbegin;
                left->tend = mid;
            }
            left->set(x, new_value);
        }
        else
        {
            if(right == NULL)
            {
                right = new node_t;
                mid++;
                right->tbegin = mid;
                right->tend = tend;
            }
            right->set(x, new_value);
        }
        value = max((left  != NULL) ? left->value : 0,
                    (right != NULL) ? right->value : 0);
    }
    uint64_t get(int64_t sbegin, int64_t send)
    {
        if(send < tbegin or tend < sbegin)
            return 0;
        else if(sbegin <= tbegin and tend <= send)
            return value;
        else
            return max(( left != NULL) ?  left->get(sbegin, send) : 0,
                       (right != NULL) ? right->get(sbegin, send) : 0);
    }
    ~node_t()
    {
        if(left  != NULL)
        {
            delete left;
            left = NULL;
        }
        if(right != NULL)
        {
            delete right;
            right = NULL;
        }
    }
};

struct segment_tree
{
    node_t root;
    segment_tree()
    {
        root.value = 0;
        root.tbegin = -MAX_COOR+1;
        root.tend = MAX_COOR;
    }
    void set(int64_t x, uint64_t new_value)
    {
        root.set(x, new_value);
    }
    uint64_t get(int64_t sbegin, int64_t send)
    {
        //cout << "get " << sbegin << ".." << send << " = " << root.get(sbegin, send) << endl;
        return root.get(sbegin, send);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t n;
    cin >> n;
    static pair_i64 A[MAX];
    for(uint64_t i = 0; i < n; i++)
    {
        cin >> A[i].second >> A[i].first;
        if(A[i].first < 0 or abs(A[i].second) > A[i].first)
            i--, n--;
    }
    sort(A, A + n);
    vector<pair<int64_t, uint64_t> > to_set_l, to_set_r;
    segment_tree ltree, rtree;
    for(uint64_t i = 0; i < n; i++)
    {
        int64_t cx = A[i].second, cy = A[i].first;
        if(cy > 5) break;
        int64_t lx = cx - cy, rx = cx + cy;
        uint64_t v = min(ltree.get(lx, MAX_COOR-10), rtree.get(-MAX_COOR+10, rx)) + 1;
        cout << cx << ", " << cy << ": " << lx << " " << rx << " -> " << v << endl;
        for(int64_t c = -10; c <= 10; c++)
            cout << ltree.get(c, c) << " "; cout << endl;
        for(int64_t c = -10; c <= 10; c++)
            cout << rtree.get(c, c) << " "; cout << endl;
        to_set_l.push_back(make_pair(lx, v));
        to_set_r.push_back(make_pair(rx, v));
        if(i == n - 1 or A[i].first != A[i+1].first)
        {
            for(uint64_t j = 0; j < to_set_l.size(); j++)
                ltree.set(to_set_l[j].first, to_set_l[j].second);
            to_set_l.clear();
            for(uint64_t j = 0; j < to_set_r.size(); j++)
                rtree.set(to_set_r[j].first, to_set_r[j].second);
            to_set_r.clear();
        }
    }
    cout << max(ltree.root.value, rtree.root.value);
}
