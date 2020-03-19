#include <bits/stdc++.h>

using namespace std;

struct cover_tree
{
    int w;

    struct node
    {
        int nodeL, nodeR;
        pair<int, int> value;
        int inc = 0;
        node *left_ptr = nullptr, *right_ptr = nullptr;

        node(int L, int R) : nodeL(L), nodeR(R), value({0, nodeR-nodeL+1}) {}

        static pair<int, int> f(pair<int, int> a, pair<int, int> b)
        {
            if(a.first == b.first)
                return {a.first, a.second + b.second};
            else
                return min(a, b);
        }

        int midi() { return nodeL + (nodeR-nodeL)/2; }
        node& left()
        {
            return *( left_ptr ?  left_ptr :  left_ptr = new node {nodeL, midi()});
        }
        node& right()
        {
            return *(right_ptr ? right_ptr : right_ptr = new node {midi()+1, nodeR});
        }

        void pull()
        {
            if(nodeL < nodeR)
                left().inc += inc, right().inc += inc;
            value.first += inc;
            inc = 0;
        }

        void update(int L, int R, int delta)
        {
            pull();
            if(nodeR < L or R < nodeL)
                return;
            else if(L <= nodeL and nodeR <= R)
                inc += delta, pull();
            else
            {
                left().update(L, R, delta);
                right().update(L, R, delta);
                value = f(left().value, right().value);
            }
        }
        pair<int, int> get(int L, int R)
        {
            pull();
            if(nodeR < L or R < nodeL)
                return {INT_MAX, 0};
            else if(L <= nodeL and nodeR <= R)
                return value;
            else
                return f(left().get(L, R), right().get(L, R));
        }

        ~node()
        {
            if(left_ptr) delete left_ptr;
            if(right_ptr) delete right_ptr;
        }
    } root;

    cover_tree(int n) : w(1 << __lg(2*n-1)), root(0, w-1) {}
    cover_tree() : cover_tree(1 << 29) {}

    void increment(int L, int R) { root.update(L, R, 1); }
    void decrement(int L, int R) { root.update(L, R, -1); }
    int cover() const
    {
        auto [v, c] = root.value;
        if(v == 0) return w - c;
        else return w;
    }
};

struct query_t
{
    int x, y1, y2;
    bool start;
};
bool operator< (const query_t& lhs, const query_t& rhs)
{
    return lhs.x < rhs.x;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    array<vector<query_t>, 16> queries;

    while(n --> 0)
    {
        int x1, y1, x2, y2, p;
        cin >> x1 >> y1 >> x2 >> y2 >> p;

        for(int dx = 0; dx < 4 and x1+dx <= x2; dx++)
         for(int dy = 0; dy < 4 and y1+dy <= y2; dy++)
          if(p >> (4*dx + dy) & 1)
        {
            auto g = 4*((x1+dx)%4) + (y1+dy)%4;
            auto gx1 = x1+dx, gy1 = y1+dy, gx2 = x2, gy2 = y2;
            while(gx2 % 4 != (x1+dx)%4) gx2--;
            while(gy2 % 4 != (y1+dy)%4) gy2--;
            gx1 /= 4; gy1 /= 4; gx2 /= 4; gy2 /= 4;
            queries[g].push_back({gx1,   gy1, gy2, true});
            queries[g].push_back({gx2+1, gy1, gy2, false});
        }
    }

    int64_t result = 0;
    cover_tree tree;
    for(size_t g = 0; g < 16; g++)
    {
        auto& Q = queries[g];
        auto m = Q.size();
        sort(Q.begin(), Q.end());
        int lastX = -1;
        for(size_t a = 0, b = 0; a < m; a = b, b = a)
        {
            auto X = queries[g][a].x;
            result += (int64_t) tree.cover() * (X - lastX);
            while(b < m and X == Q[b].x) b++;
            for(size_t i = a; i < b; i++)
            {
                if(Q[i].start)
                    tree.increment(Q[i].y1, Q[i].y2);
                else
                    tree.decrement(Q[i].y1, Q[i].y2);
            }
            lastX = X;
        }
    }

    cout << result << endl;
}
