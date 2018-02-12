#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500000;
const size_t TSIZE = 1 << 20, THEIGHT = 19;
const size_t MAX_E = 100000;

struct interval_tree
{
    uint32_t n = TSIZE/2-1;
    array<int32_t, TSIZE> values, to_add;
    void apply(uint32_t i, int32_t value)
    {
        values[i] += value;
        if(i < n)
            to_add[i] += value;
    }
    void build(uint32_t i)
    {
        while(i > 1)
            i /= 2, values[i] = max(values[2*i], values[2*i+1]) + to_add[i];
    }
    void push(uint32_t p)
    {
        for(uint32_t s = THEIGHT; s --> 0;)
        {
            uint32_t i = p >> s;
            if(to_add[i])
            {
                apply(2*i, to_add[i]);
                apply(2*i+1, to_add[i+1]);
                to_add[i] = 0;
            }
        }
    }
    void increment_interval(uint32_t sbegin, uint32_t send)
    {
        sbegin += n; send += n + 1;
        uint32_t sbegin0 = sbegin, send0 = send;
        for(; sbegin < send; sbegin /= 2, send /= 2)
        {
            if(sbegin & 1)
                apply(sbegin++, 1);
            if(send & 1)
                apply(--send, 1);
        }
        build(sbegin0);
        build(send0 - 1);
    }
    void decrement_interval(uint32_t sbegin, uint32_t send)
    {
        sbegin += n; send += n + 1;
        uint32_t sbegin0 = sbegin, send0 = send;
        for(; sbegin < send; sbegin /= 2, send /= 2)
        {
            if(sbegin & 1)
                apply(sbegin++, -1);
            if(send & 1)
                apply(--send, -1);
        }
        build(sbegin0);
        build(send0 - 1);
    }
    int32_t find_value(uint32_t sbegin, uint32_t send)
    {
        sbegin += n; send += n + 1;
        push(sbegin); push(send - 1);
        int32_t r = 0;
        for(; sbegin < send; sbegin /= 2, send /= 2)
        {
            if(sbegin & 1)
                r = max(r, values[sbegin++]);
            if(send & 1)
                r = max(r, values[--send]);
        }
        return r;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    fstream cin("temp/temp.in");
    cin >> n;
    static array<uint32_t, MAX> A;
    static array<uint32_t, MAX_E+1> PI;
    static array<vector<uint32_t>, MAX_E+1> P;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i], P[A[i]].push_back(i);
    static interval_tree tree;
    int32_t r = 0;
    for(uint32_t i = 1; i <= MAX_E; i++)
    {
        if(P[i].empty()) continue;
        tree.increment_interval(P[i][0], P[i].size() > 1 ? P[i][1] - 1 : n - 1);
    }
    r = max(r, tree.find_value(0, n-1));
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t p = PI[A[i]];
        tree.decrement_interval(P[A[i]][p], p + 1 < P[A[i]].size() ? P[A[i]][p+1] - 1 : n - 1);
        p++; PI[A[i]]++;
        if(p < P[A[i]].size())
        {
            tree.increment_interval(P[A[i]][p], p + 1 < P[A[i]].size() ? P[A[i]][p+1] - 1 : n - 1);
            r = max(r, tree.find_value(i+1, n-1));
        }
    }
    cout << r;
}
