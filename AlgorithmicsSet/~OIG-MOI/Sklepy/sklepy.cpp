#include <bits/stdc++.h>
 
using namespace std;
 
typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;
 
const size_t MAX = 500001;
 
template<typename T, size_t S>
struct arrayc
{
    T _arr[S];
    const T& operator[](uint32_t i) const
    {
        return _arr[i];
    }
    T& operator[](uint32_t i)
    {
        return _arr[i];
    }
};
 
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    uint64_t base_total = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        uint64_t c;
        cin >> c;
        base_total += c;
    }
    static arrayc<uint64_t, MAX+1> R, L;
    for(uint32_t i = 0; i < n - 1; i++)
        cin >> R[i];
    for(uint32_t i = 1; i < n; i++)
        cin >> L[i];
    static arrayc<vector<uint32_t>, MAX> graph, reverse_graph;
    for(uint32_t i = 0; i < n - 1; i++)
    {
        if(R[i] < L[i+1])
            graph[i].push_back(i+1), reverse_graph[i+1].push_back(i);
        else
            graph[i+1].push_back(i), reverse_graph[i].push_back(i);
    }
    static arrayc<uint32_t, MAX> T; uint32_t ti = 0;
    static arrayc<uint32_t, MAX> leading_to;
    queue<uint32_t> Q;
    for(uint32_t i = 0; i < n; i++)
        if(reverse_graph[i].empty())
            Q.push(i);
        else
            leading_to[i] = reverse_graph[i].size();
    uint64_t total = base_total;
    while(not Q.empty())
    {
        uint32_t u = Q.front(); Q.pop();
        T[ti++] = u;
        for(uint32_t i = 0; i < graph[u].size(); i++)
        {
            uint32_t v = graph[u][i];
            if(v < u)
                total += L[u];
            else
                total += R[u];
            leading_to[v]--;
            if(not leading_to[v])
                Q.push(v);
        }
    }
    cout << total << '\n';
    for(uint32_t i = 0; i < ti; i++)
        cout << T[i]+1 << " ";
}
				