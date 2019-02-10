#include <bits/stdc++.h>

using namespace std;

const size_t MAX_M = 20, MAX_C = 1000, MAX_T = 4 * MAX_M * MAX_C;

uint32_t bit_get(uint32_t x, uint32_t i) { return x & (1u << i); }
uint32_t bit_set0(uint32_t x, uint32_t i) { return x & ~(1u << i); }
uint32_t bit_set1(uint32_t x, uint32_t i) { return x | (1u << i); }

template<typename T, size_t N>
struct value_scaler
{
    uint32_t maxim;
    T _A[N];
    unordered_map<T, size_t> M;
    template<typename Iterator>
    value_scaler(Iterator begin, Iterator end)
    {
        size_t n = 0;
        for(auto it = begin; it != end; it++)
            _A[n] = *it, n++;
        sort(_A, _A + n);
        M.reserve(2*n);
        maxim = 0;
        for(size_t i = 0, f = 0; i < n; i++)
        {
            if(i > 0 and _A[i-1] == _A[i])
                f++;
            M[_A[i]] = i - f;
            maxim = max(maxim, i - f);
        }
    }
    const size_t& operator[] (const T& x) { return M[x]; }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t m, endtime;
    cin >> m >> endtime;
    static vector<pair<uint32_t, uint32_t>> shows[MAX_C];
    vector<uint32_t> all_times;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t d, c;
        cin >> d >> c;
        for(uint32_t j = 0; j < c; j++)
        {
            uint32_t a;
            cin >> a;
            uint32_t b = min(a + d, endtime + 1);
            all_times.push_back(a); all_times.push_back(b);
            shows[i].emplace_back(a, b);
        }
    }
    static value_scaler<uint32_t, MAX_T>
        time_transform(all_times.begin(), all_times.end());
    endtime = time_transform.maxim;
    static vector<pair<uint32_t, uint32_t>> begins[MAX_T], ends[MAX_T];
    static uint32_t t_end[MAX_M][MAX_C];
    static bitset<MAX_C> is_begin[MAX_M], is_end[MAX_M];
    queue<pair<pair<uint32_t, uint32_t>, pair<uint32_t, uint32_t>>> Q;
    static uint32_t V[1u << MAX_M];
    for(uint32_t i = 0; i < m; i++)
    {
        for(uint32_t j = 0; j < shows[i].size(); j++)
        {
            auto p = shows[i][j];
            p.first  = time_transform[p.first];
            p.second = time_transform[p.second];
            //cout << i << ":" << j << " " << p.first << ".." << p.second << endl;
            begins[p.first].emplace_back(i, j);
            ends[p.second].emplace_back(i, j);
            t_end[i][j] = p.second;
            if(p.first == 0)
            {
                is_begin[i][j] = true;
                Q.emplace(make_pair(i, j), make_pair(1u << i, 1));
                V[1u << i] = p.second;
            }
            if(p.second >= endtime)
            {
                //cout << "$ " << i << " " << j << endl;
                is_end[i][j] = true;
            }
        }
    }
    map<uint32_t, uint32_t> last_active;
    set<pair<uint32_t, uint32_t>> active;
    vector<pair<uint32_t, uint32_t>> graph[MAX_M][MAX_C];
    for(uint32_t t = 0; t <= endtime; t++)
    {
        //cout << t << ": ";
        for(auto p : begins[t])
        {
            active.emplace(p.first, p.second);
            last_active[p.first] = p.second;
        }
        for(auto it1 = active.begin(); it1 != active.end(); ++it1)
        {
            //cout << it1->first << ":" << it1->second << " ";
            for(auto it2 = last_active.begin(); it2 != last_active.end(); ++it2)
            {
                if(it1->first == it2->first)
                    continue;
                bool ok = true;
                for(auto e : graph[it1->first][it1->second])
                {
                    if(e.first == it2->first and e.second == it2->second)
                    {
                        ok = false;
                        break;
                    }
                }
                if(ok) for(auto e : graph[it2->first][it2->second])
                {
                    if(e.first == it1->first and e.second == it1->second)
                    {
                        ok = false;
                        break;
                    }
                }
                if(ok)
                {
                    uint32_t a = t_end[it1->first][it1->second],
                             b = t_end[it2->first][it2->second];
                    if(a < b)
                        graph[it1->first][it1->second].emplace_back(*it2);
                    else if(a > b)
                        graph[it2->first][it2->second].emplace_back(*it1);
                }
            }
        }
        //cout << endl;
        for(auto p : ends[t])
        {
            active.erase(p);
            auto it = last_active.find(p.first);
            if(p.second == it->second)
                last_active.erase(it);
        }
    }
    while(not Q.empty())
    {
        auto p = Q.front(); Q.pop();
        pair<uint32_t, uint32_t> u; uint32_t m, d;
        u = p.first; m = p.second.first; d = p.second.second;
        if(V[m] > t_end[u.first][u.second])
            continue;
        //cout << u.first << ":" << u.second << " " << bitset<4>(m) << " " << d << endl;
        if(is_end[u.first][u.second])
        {
            cout << d;
            return 0;
        }
        for(auto v : graph[u.first][u.second])
        {
            uint32_t mx = bit_set1(m, v.first);
            //cout << "-> " << v.first << " " << v.second;
            if(not bit_get(m, v.first) and t_end[v.first][v.second] > V[mx])
            {
                //cout << " +";
                Q.emplace(v, make_pair(mx, d + 1));
                V[mx] = t_end[v.first][v.second];
            }
            //cout << endl;
        }
    }
    cout << -1;
}
