#include <bits/stdc++.h>
#include <ext/functional>

using namespace std;
using __gnu_cxx::identity_element;

const size_t MAX = 1 << 20;

uint32_t identity_element(bit_xor<uint32_t>) { return 0; }
template<typename T, typename ChildrenOp>
struct segment_tree
{
    vector<T> values;
    size_t w;
    ChildrenOp F;
    segment_tree(size_t n, ChildrenOp f = {})
    {
        F = move(f);
        w = (31 - __builtin_clz(2*n-1));
        values.resize(2*w, identity_element(F));
    }
    void set(size_t i, T value)
    {
        i += w;
        values[i] = value; i /= 2;
        while(i) values[i] = F(values[2*i], values[2*i+1]), i /= 2;
    }
    T get(size_t getL, size_t getR)
    {
        T result = identity_element(F);
        for(getL += w, getR += w+1; getL < getR; getL /= 2, getR /= 2)
        {
            if(getL % 2) result = F(result, values[getL++]);
            if(getR % 2) result = F(result, values[--getR]);
        }
        return result;
    }
};
typedef segment_tree<uint32_t, bit_xor<uint32_t>> xor_tree;
typedef segment_tree<uint32_t, plus<uint32_t>> sum_tree;

typedef pair<pair<uint32_t, uint32_t>, set<uint32_t>> canditerval_t;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    map<pair<uint32_t, uint32_t>, uint32_t> intervals_idx;
    static pair<uint32_t, uint32_t> intervals[MAX];
    static uint32_t answers[MAX];
    xor_tree ans_tree(n), pop_tree(n);
    set<uint32_t> pop;
    queue<uint32_t> todo;
    for(uint32_t i = 0; i < m; i++)
    {
        pair<uint32_t, uint32_t> p;
        cin >> p.first >> p.second >> answers[i]; p.first--; p.second--;
        if(intervals_idx.find(p) != intervals_idx.end())
            { i--; m--; continue; }
        intervals[i] = p;
        if(p.first == p.second) todo.push(i);
        else intervals_idx[p] = i;
    }
    for(uint32_t i = 0; i < n; i++)
        pop.insert(i);
    while(not todo.empty())
    {
        uint32_t c = todo.front(); todo.pop();
        auto it = pop.lower_bound(intervals[c].first);
        uint32_t d = *it;
        uint32_t g1 = (intervals[c].first<d ?
                            ans_tree.get(intervals[c].first, d-1) : 0),
                 g2 = (d<intervals[c].second ?
                            ans_tree.get(d+1, intervals[c].second) : 0);
        ans_tree.set(d, g1 ^ g2);
        //cout << "handle " << c << ": " << intervals[c].first << ".." << intervals[c].second << endl;
        //cout << "set " << d << " := " << (g1^g2) << endl;
        pop_tree.set(d, 1);
        if(pop.size() == 1) { pop.erase(it); break; }
        auto it1 = it, it2 = it; it1--; it2++;
#define HANDLE \
            bool done = false;                                          \
            while(not done)                                             \
            {                                                           \
                auto it = intervals_idx.lower_bound({a, a});            \
                if(it == intervals_idx.end()) done = true;              \
                else                                                    \
                {                                                       \
                    uint32_t i = it->first.first, j = it->first.second; \
                    if(j <= b and pop_tree.get(i, j) == j-i)            \
                    {                                                   \
                        todo.push(it->second);                          \
                        intervals_idx.erase(it);                        \
                    }                                                   \
                    else                                                \
                        done = true;                                    \
                }                                                       \
            }
        //cout << "{ ";
        //for(uint32_t x : pop)
        //    cout << x << " "; cout << "}" << endl;
        if(it != pop.begin()) // it1 center
        {
            //cout << "left " << *it1 << endl;
            auto ita = it1; ita--;
            uint32_t a = 0, b = n-1;
            if(it1 != pop.begin())
                a = *ita + 1;
            if(it2 != pop.end())
                b = *it2 - 1;
            //cout << "[1] try find " << a << ".." << b << endl;
            HANDLE;
        }
        if(it2 != pop.end()) // it2 center
        {
            //cout << "right " << *it2 << endl;
            auto itb = it2; itb++;
            uint32_t a = 0, b = n-1;
            if(it != pop.begin())
                a = *it1 + 1;
            if(itb != pop.end())
                b = *itb - 1;
            //cout << "[2] try find " << a << ".." << b << endl;
            HANDLE;
        }
        pop.erase(it);

    }
    if(pop_tree.get(0, n-1) == n)
    {
        for(uint32_t i = 0; i < n; i++)
            cout << ans_tree.values[ans_tree.w + i] << " ";
    }
    else
        cout << "NIE";
}
