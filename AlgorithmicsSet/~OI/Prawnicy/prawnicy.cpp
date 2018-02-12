#include <bits/stdc++.h>

using namespace std;

typedef pair<uint32_t, uint32_t> pair_u32;

const size_t MAX = 1000000;
const size_t TSIZE = 1 << 22;

struct bitter_tree
{
    array<uint32_t, TSIZE> values;
    void push(uint32_t i)
    {
        i += TSIZE/2;
        values[i]++;
        while(i)
            i--, i /= 2, values[i]++;
    }
    void pop(uint32_t i)
    {
        i += TSIZE/2;
        values[i]--;
        while(i)
            i--, i /= 2, values[i]--;
    }
    uint32_t find_k(uint32_t k)
    {
        uint32_t node = 0, tbegin = 0, tend = TSIZE / 2 - 1;
        while(tbegin < tend)
        {
            if(values[2*node+1] < k)
            {
                k -= values[2*node+1];
                node *= 2; node += 2;
                tbegin = (tbegin+tend)/2 + 1;
            }
            else
            {
                node *= 2; node++;
                tend = (tbegin+tend)/2;
            }
        }
        return tbegin - 1;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    static array<pair_u32, MAX> intervals, begins, ends;
    unordered_map<uint32_t, uint32_t> M;
    M.reserve(2*MAX);
    static array<uint32_t, 2*MAX> RM, V; uint32_t vi = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> intervals[i].first >> intervals[i].second;
        V[vi++] = intervals[i].first; V[vi++] = intervals[i].second;
    }
    sort(V.begin(), V.begin() + vi);
    for(uint32_t i = 0, f = 0; i < vi; i++)
    {
        if(i > 0 and V[i] == V[i-1]) f++;
        M[V[i]] = i - f;
        RM[i - f] = V[i];
    }
    for(uint32_t i = 0; i < n; i++)
    {
        intervals[i].first = M[intervals[i].first];
        intervals[i].second = M[intervals[i].second];
        begins[i].first = intervals[i].first; begins[i].second = i;
        ends[i].first = intervals[i].second; ends[i].second = i;
    }
    M.clear();
    sort(begins.begin(), begins.begin() + n);
    sort(ends.begin(), ends.begin() + n);
    uint32_t a = 0, b = 0, active_count = 0, result_length = 0, result_time = 0;
    static bitter_tree active;
    while(a < n or b < n)
    {
        if(b >= n or (a < n and begins[a].first <= ends[b].first))
        {
            active.push(begins[a].first);
            active_count++;
            a++;
        }
        else
        {
            if(active_count >= k)
            {
                uint32_t length = RM[ends[b].first] - RM[active.find_k(k)];
                if(length > result_length)
                {
                    result_length = length;
                    result_time = ends[b].first;
                }
            }
            active.pop(intervals[ends[b].second].first);
            active_count--;
            b++;
        }
    }
    static array<bool, MAX> is_active;
    a = 0; b = 0;
    while(a < n or b < n)
    {
        if(b >= n or (a < n and begins[a].first <= ends[b].first))
        {
            is_active[begins[a].second] = true;
            active_count++;
            a++;
        }
        else
        {
            if(ends[b].first == result_time)
                break;
            is_active[ends[b].second] = false;
            active_count--;
            b++;
        }
    }
    set<pair_u32> result;
    for(uint32_t i = 0; i < n; i++)
        if(is_active[i])
            result.emplace(RM[intervals[i].first], i);
    cout << result_length << endl;
    uint32_t i = 0;
    for(pair_u32 p : result)
    {
        if(i >= k) break;
        cout << p.second + 1 << " ";
        i++;
    }
}
