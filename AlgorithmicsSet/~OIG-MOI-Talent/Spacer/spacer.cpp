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
    node_t* alloc_next_node()
    {
        static node_t prealloc[1<<20];
        static size_t i = 0;
        node_t* r = prealloc+i;
        i++;
        return r;
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
                left = alloc_next_node();
                left->tbegin = tbegin;
                left->tend = mid;
            }
            left->set(x, new_value);
        }
        else
        {
            if(right == NULL)
            {
                right = alloc_next_node();
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
    set<pair_i64> S; //
    for(uint64_t i = 0; i < n; i++)
    {
        int64_t x, y;
        cin >> x >> y;
        if(y < 0 or abs(x) > y or S.find(make_pair(x, y)) != S.end())
        {
            i--, n--;
            continue;
        }
        S.insert(make_pair(x, y));
        A[i].first = x - y;
        A[i].second = -(x + y);
    }
    sort(A, A + n);
    static segment_tree tree;
    for(uint64_t i = n; i --> 0;)
    {
        int64_t x = A[i].first, y = -A[i].second;
        tree.set(y, tree.get(-MAX_COOR+1, y) + 1);
    }
    cout << tree.root.value;
}
