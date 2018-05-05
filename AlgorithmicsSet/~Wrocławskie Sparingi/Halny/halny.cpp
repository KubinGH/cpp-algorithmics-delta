#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 5e5, TSIZE = 1 << 20;

template<typename T, size_t N>
struct value_scaler
{
    pair<T, size_t> _A[N];
    unordered_map<T, size_t> M;
    template<typename Iterator>
    value_scaler(Iterator begin, Iterator end)
    {
        size_t n = 0;
        for(auto it = begin; it != end; it++)
        {
            _A[n].first = *it; _A[n].second = n;
            n++;
        }
        sort(_A, _A + n);
        M.reserve(N);
        for(size_t i = 0, f = 0; i < n; i++)
        {
            if(i > 0 and _A[i].first == _A[i-1].first)
                f++;
            M[_A[i].first] = i - f;
        }
    }
    const size_t& operator[] (const T& x)
    {
        return M[x];
    }
};

struct segment_tree
{
    uint32_t values[TSIZE];
    void set(uint32_t i, uint32_t v)
    {
        i += TSIZE/2;
        if(v < values[i])
            return;
        values[i] = v;
        while(i > 1)
            i /= 2, values[i] = max(values[2*i], values[2*i+1]);
    }
    uint32_t get(uint32_t i, uint32_t tbegin, uint32_t tend,
                             uint32_t sbegin, uint32_t send)
    {
        if(send < tbegin or tend < sbegin)
            return 0;
        else if(sbegin <= tbegin and tend <= send)
            return values[i];
        else
            return max(get(2*i,   tbegin, (tbegin+tend)/2, sbegin, send),
                       get(2*i+1, (tbegin+tend)/2+1, tend, sbegin, send));
    }
    uint32_t get(uint32_t sbegin, uint32_t send)
    {
        return get(1, 0, TSIZE/2-1, sbegin, send);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static uint32_t height[MAX], strength[MAX];
    for(uint32_t i = 0; i < n; i++)
        cin >> height[i] >> strength[i];
    static value_scaler<uint32_t, MAX> height_T(height, height + n);
    for(uint32_t i = 0; i < n; i++)
        height[i] = height_T[height[i]];
    static segment_tree strength_tree;
    static uint32_t actual_strength[MAX], goals[MAX];
    for(uint32_t i = 0; i < n; i++)
    {
        actual_strength[i] = max(strength[i], strength_tree.get(height[i], TSIZE/2-1));
        strength_tree.set(height[i], strength[i]);
        goals[i] = actual_strength[i];
    }
    sort(goals, goals + n);
    uint32_t lo = 0;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t s;
        cin >> s;
        uint32_t nlo = upper_bound(goals + lo, goals + n, s) - goals;
        cout << nlo - lo << "\n";
        lo = nlo;
    }
}
