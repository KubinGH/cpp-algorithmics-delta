#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500000;
const size_t TSIZE = 1 << 20;
const size_t MAX_E = 100000;

struct interval_tree
{
    array<int32_t, TSIZE> values, to_add;
    void push_down(uint32_t i, uint32_t tbegin, uint32_t tend)
    {
        if(to_add[i] == 0)
            return;
        values[i] += to_add[i];
        if(tbegin != tend)
        {
            to_add[2*i+1] += to_add[i];
            to_add[2*i+2] += to_add[i];
        }
        to_add[i] = 0;
    }
    template<int32_t value>
    void add_to_interval(uint32_t i, uint32_t tbegin, uint32_t tend, uint32_t sbegin, uint32_t send)
    {
        if(tend < sbegin or send < tbegin)
            return;
        if(sbegin <= tbegin and tend <= send)
            to_add[i] += value, push_down(i, tbegin, tend);
        else
        {
            push_down(i, tbegin, tend);
            add_to_interval<value>(2*i+1, tbegin, (tbegin+tend)/2, sbegin, send);
            add_to_interval<value>(2*i+2, (tbegin+tend)/2+1, tend, sbegin, send);
            values[i] = max(values[2*i+1]+to_add[2*i+1], values[2*i+2]+to_add[2*i+2]);
        }
    }
    template<int32_t value>
    void add_to_interval(uint32_t sbegin, uint32_t send)
    {
        add_to_interval<value>(0, 0, TSIZE/2-1, sbegin, send);
    }
    int32_t find_value(uint32_t i, uint32_t tbegin, uint32_t tend, uint32_t sbegin, uint32_t send)
    {
        if(tend < sbegin or send < tbegin)
            return 0;
        push_down(i, tbegin, tend);
        if(sbegin <= tbegin and tend <= send)
            return values[i];
        else
            return max(find_value(2*i+1, tbegin, (tbegin+tend)/2, sbegin, send),
                       find_value(2*i+2, (tbegin+tend)/2+1, tend, sbegin, send));
    }
    int32_t find_value(uint32_t sbegin, uint32_t send)
    {
        return find_value(0, 0, TSIZE/2-1, sbegin, send);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
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
        tree.add_to_interval<1>(P[i][0], P[i].size() > 1 ? P[i][1] - 1 : n - 1);
    }
    r = max(r, tree.find_value(0, n-1));
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t& p = PI[A[i]];
        tree.add_to_interval<-1>(P[A[i]][p], p + 1 < P[A[i]].size() ? P[A[i]][p+1] - 1 : n - 1);
        p++;
        if(p < P[A[i]].size())
            tree.add_to_interval<1>(P[A[i]][p], p + 1 < P[A[i]].size() ? P[A[i]][p+1] - 1 : n - 1);
        r = max(r, tree.find_value(i+1, n-1));
    }
    cout << r;
}
