#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

const int FIX = 1e9;
const size_t NAX = (1u << 31) - 1;

struct point
{
    int x, y;
};

constexpr size_t lsb(size_t x) { return x & -x; }

struct segment_tree
{
    struct node
    {
        unique_ptr<node> left_ptr, right_ptr;
        int value = 0;
        node* left()
        {
            if(not left_ptr)
                left_ptr = unique_ptr<node>(new node);
            return left_ptr.get();
        }
        node* right()
        {
            if(not right_ptr)
                right_ptr = unique_ptr<node>(new node);
            return right_ptr.get();
        }

        int get(size_t nodeL, size_t nodeR, size_t queryL, size_t queryR)
        {
            if(nodeR < queryL or queryR < nodeL)
                return 0;
            else if(queryL <= nodeL and nodeR <= queryR)
                return value;
            else
                return max(
                    left()->get(nodeL, (nodeL+nodeR)/2, queryL, queryR),
                    right()->get((nodeL+nodeR)/2+1, nodeR, queryL, queryR)
                );
        }
    } root;

    int get(size_t l, size_t r)
    {
        return root.get(0, NAX, l, r);
    }

    void set(size_t p, int v)
    {
        node* curr = &root;
        size_t nodeL = 0, nodeR = NAX;
        while(nodeL < nodeR)
        {
            size_t mid = (nodeL + nodeR) / 2;
            curr->value = max(curr->value, v);
            if(p <= mid)
                curr = curr->left(), nodeR = mid;
            else
                curr = curr->right(), nodeL = mid+1;
        }
        curr->value = max(curr->value, v);
    }

};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<point> points(n);
    for(size_t i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        points[i] = {x + FIX, FIX - y};
    }

    sort(points.begin(), points.end(), [&](point a, point b) {
        return make_pair(a.x - a.y, a.x) < make_pair(b.x - b.y, b.x);
    });

    segment_tree T;

    vector<pair<size_t, size_t>> Y;
    for(size_t i = 0; i < points.size(); i++)
        Y.emplace_back(points[i].y, i);
    sort(Y.begin(), Y.end());

    for(size_t i = 0, f = 0; i < points.size(); i++)
    {
        if(i and Y[i].first != Y[i-1].first)
            f++;
        points[Y[i].second].y = f;
    }


    for(auto p : points)
        T.set(p.y, T.get(0, p.y) + 1);

    cout << T.get(0, NAX);
}
