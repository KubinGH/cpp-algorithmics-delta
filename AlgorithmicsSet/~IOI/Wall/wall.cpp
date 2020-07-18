#include <bits/stdc++.h>

using namespace std;

struct clamp_op
{
    int a, b;
    int operator() (int x)
    {
        return min(max(x, a), b);
    }
} clamp_id = {INT_MIN, INT_MAX};

clamp_op operator>> (clamp_op F, clamp_op G)
{
    if(F.b < G.a)
        return {G.a, G.a};
    else if(G.b < F.a)
        return {G.b, G.b};
    else
        return {max(F.a, G.a), min(F.b, G.b)};
}
clamp_op& operator>>= (clamp_op& F, clamp_op G)
{
    return F = F >> G;
}
ostream& operator<< (ostream& out, clamp_op F)
{
    return out << "clamp_op{" << F.a << ", " << F.b << "}";
}

struct segment_tree
{
    size_t w;
    vector<clamp_op> values;

    segment_tree(size_t n) : w(1 << __lg(2*n - 1)), values(2*w, clamp_id) {}

    void push(size_t i)
    {
        if(i < w)
        {
            values[2*i+0] >>= values[i];
            values[2*i+1] >>= values[i];
            values[i] = clamp_id;
        }
    }

    void mut(size_t i, size_t nodeL, size_t nodeR, size_t L, size_t R, clamp_op F)
    {
        push(i);
        if(nodeR < L or R < nodeL)
            return;
        else if(L <= nodeL and nodeR <= R)
            values[i] >>= F;
        else
            mut(2*i+0, nodeL, (nodeL+nodeR)/2, L, R, F),
            mut(2*i+1, (nodeL+nodeR)/2+1, nodeR, L, R, F);
    }

    void mut(size_t L, size_t R, clamp_op F)
    {
        return mut(1, 0, w-1, L, R, F);
    }
};

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int out[])
{
    segment_tree tree(n);
    for(int i = 0; i < k; i++)
    {
        auto f = op[i] == 1 ? clamp_op{height[i], INT_MAX} : clamp_op{INT_MIN, height[i]};
        tree.mut(left[i], right[i], f);
    }
    for(int i = 1; i < (int)tree.w; i++)
        tree.push(i);
    for(int i = 0; i < n; i++)
        out[i] = tree.values[tree.w + i](0);
}

#ifdef XHOVA
int main()
{
    int out[10];
    int op[] = {1, 2, 2, 1, 1, 2}, left[] = {1, 4, 3, 0, 2, 6}, right[] = {8, 9, 6, 5, 2, 7}, height[] = {4, 1, 5, 3, 5, 0};
    buildWall(10, 6, op, left, right, height, out);
    for(auto x : out)
        cout << x << " ";
    cout << endl;
}
#endif
