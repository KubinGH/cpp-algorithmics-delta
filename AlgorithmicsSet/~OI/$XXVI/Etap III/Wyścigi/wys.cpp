#include <bits/stdc++.h>

using namespace std;

const int64_t oo = (1ll << 50);

struct segment_tree
{
    size_t w;
    vector<int64_t> values, mutate;
    segment_tree(size_t n)
    {
        w = 1 << __lg(2*n-1);
        values.resize(2*w, -oo);
        mutate.resize(2*w);
    }

    void pull(size_t i, size_t nodeL, size_t nodeR)
    {
        if(not mutate[i])
            return;
        if(nodeL < nodeR)
        {
            mutate[2*i] += mutate[i];
            mutate[2*i+1] += mutate[i];
        }
        values[i] += mutate[i];
        mutate[i] = 0;
    }

    int64_t get(size_t i, size_t nodeL, size_t nodeR, size_t getL, size_t getR)
    {
        pull(i, nodeL, nodeR);
        if(getR < nodeL or nodeR < getL)
            return -oo;
        else if(getL <= nodeL and nodeR <= getR)
            return values[i];
        else
            return max(get(2*i, nodeL, (nodeL+nodeR)/2, getL, getR),
                       get(2*i+1, (nodeL+nodeR)/2+1, nodeR, getL, getR));
    }

    int64_t get(size_t getL, size_t getR) { return getL <= getR ? get(1, 0, w-1, getL, getR) : -oo; }

    void mut(size_t i, size_t nodeL, size_t nodeR, size_t getL, size_t getR, int64_t value)
    {
        pull(i, nodeL, nodeR);
        if(getR < nodeL or nodeR < getL)
            return;
        else if(getL <= nodeL and nodeR <= getR)
        {
            mutate[i] += value;
            pull(i, nodeL, nodeR);
        }
        else
        {
            mut(2*i, nodeL, (nodeL+nodeR)/2, getL, getR, value);
            mut(2*i+1, (nodeL+nodeR)/2+1, nodeR, getL, getR, value);
            values[i] = max(values[2*i], values[2*i+1]);
        }
    }

    void mut(size_t getL, size_t getR, int64_t value) { return mut(1, 0, w-1, getL, getR, value); }

    size_t search_lower_bound(int64_t x)
    {
        size_t i = 1, nodeL = 0, nodeR = w - 1;
        pull(i, nodeL, nodeR);
        while(nodeL < nodeR)
        {
            if(pull(2*i, nodeL, (nodeL+nodeR)/2), values[2*i] >= x)
                i *= 2, nodeR = (nodeL+nodeR)/2;
            else if(pull(2*i+1, (nodeL+nodeR)/2+1, nodeR), values[2*i+1] >= x)
                i *= 2, i++, nodeL = (nodeL+nodeR)/2+1;
            else
                return w;
        }
        return i - w;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    vector<int64_t> A(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    sort(A.begin(), A.end());

    segment_tree At(n), Bt(n);

    for(uint32_t i = 0; i < n; i++)
    {
        At.mut(i, i, oo + A[i]);
        Bt.mut(i, i, oo + A[i] + n - i);
    }

    uint32_t loZ = 0;
    while(q --> 0)
    {
        char c;
        cin >> c;
        if(c == 'B')
        {
            int64_t x, y;
            cin >> x >> y;
            uint32_t j = At.search_lower_bound(x);
            if(j < n)
                At.mut(j, n-1, y), Bt.mut(j, n-1, y);
        }
        else if(c == 'K')
        {
            int64_t x, y;
            cin >> x >> y;
            uint32_t j = At.search_lower_bound(x+1);
            if(j > 0)
                At.mut(0, j-1, -y), Bt.mut(0, j-1, -y);
        }
        else if(c == 'Z')
        {
            auto F = [&](uint32_t mid) { return At.get(mid, mid) + n >= max(Bt.get(0, mid) - 1ll, Bt.get(mid, n-1)); };
            while(loZ < n and not F(loZ))
                loZ++;
            cout << n - loZ << "\n";
        }
    }
}