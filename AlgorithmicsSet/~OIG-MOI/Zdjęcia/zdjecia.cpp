#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000;
const size_t MAX_C = 400000, FIX = MAX_C/2;
const size_t TSIZE = 1 << 20;

struct coor_t
{
    uint32_t x, y;
};
typedef pair<uint32_t, uint32_t> pair_u32;

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
    void add_to_interval(uint32_t i, uint32_t tbegin, uint32_t tend, uint32_t sbegin, uint32_t send, int32_t value)
    {
        if(tend < sbegin or send < tbegin)
            return;
        if(sbegin <= tbegin and tend <= send)
            to_add[i] += value, push_down(i, tbegin, tend);
        else
        {
            push_down(i, tbegin, tend);
            add_to_interval(2*i+1, tbegin, (tbegin+tend)/2, sbegin, send, value);
            add_to_interval(2*i+2, (tbegin+tend)/2+1, tend, sbegin, send, value);
            values[i] = max(values[2*i+1]+to_add[2*i+1], values[2*i+2]+to_add[2*i+2]);
        }
    }
    void add_to_interval(uint32_t sbegin, uint32_t send, int32_t value)
    {
        add_to_interval(0, 0, TSIZE/2-1, sbegin, send, value);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<pair<coor_t, coor_t>, MAX> R;
    static multimap<uint32_t, pair_u32> A, B;
    for(uint32_t i = 0; i < n; i++)
    {
        int32_t x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        R[i].first.x = x1 + FIX;  R[i].first.y = y1 + FIX;
        R[i].second.x = x2 + FIX; R[i].second.y = y2 + FIX;
        A.emplace(R[i].first.x,  pair_u32(R[i].first.y, R[i].second.y));
        B.emplace(R[i].second.x, pair_u32(R[i].first.y, R[i].second.y));
    }
    int32_t result = 0;
    auto ita = A.begin(), itb = B.begin();
    static interval_tree tree;
    while(ita != A.end() or itb != B.end())
    {
        //cout << "x " << (ita != A.end() ? ita->first : 0) << " " << (itb != B.end() ? itb->first : 0) << endl;
        if(itb == B.end() or (ita != A.end() and ita->first <= itb->first))
        {
            //cout << "add " << (int)ita->second.first - (int)FIX << " " << (int)ita->second.second - (int)FIX << endl;
            tree.add_to_interval(ita->second.first, ita->second.second, 1);
            result = max(result, tree.values[0]);
            ita++;
        }
        else
        {
            //cout << "sub " << (int)itb->second.first - (int)FIX << " " << (int)itb->second.second - (int)FIX << endl;
            tree.add_to_interval(itb->second.first, itb->second.second, -1);
            itb++;
        }
    }
    cout << result;
}
