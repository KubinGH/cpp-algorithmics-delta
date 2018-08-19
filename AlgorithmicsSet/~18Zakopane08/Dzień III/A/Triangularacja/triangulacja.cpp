#include <bits/stdc++.h>
#define NOTE_ADD(_i)        \
{                           \
    uint32_t k = K[_i];     \
    if(T[k] == 0)           \
        u++;                \
    T[k]++;                 \
    if(T[k] == S[k])        \
        u--;                \
}
#define NOTE_REMOVE(_i)     \
{                           \
    uint32_t k = K[_i];     \
    if(T[k] == S[k])        \
        u++;                \
    T[k]--;                 \
    if(T[k] == 0)           \
        u--;                \
}

#ifndef _WIN32
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

using namespace std;

const size_t MAX = 1 << 17;

template<typename T>
istream& operator>> (istream& in, complex<T>& o)
{
    T x, y;
    in >> x >> y;
    o = {x, y};
    return in;
}

template<typename T>
pair<T, T> sortedpair(T a, T b)
{
    return (a<b) ? pair<T, T>{a, b} : pair<T, T>{b, a};
}

typedef tuple<uint32_t, uint32_t, uint32_t> query_t;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    uint32_t Q = floor(sqrt(n) - 1);
    auto mo_cmp = [&](const query_t& lhs, const query_t& rhs) {
        if(get<0>(lhs) / Q != get<0>(rhs) / Q)
            return get<0>(lhs) / Q < get<0>(rhs) / Q;
        else
            return get<1>(lhs) > get<1>(rhs);
    };
    static complex<int32_t> P[MAX];
    for(uint32_t i = 0; i < n; i++)
        cin >> P[i];
    static uint32_t A[MAX], B[MAX], C[MAX], K[MAX];
    map<pair<uint32_t, uint32_t>, vector<uint32_t>> conn;
    static uint32_t S[MAX];
    for(uint32_t i = 0; i < n - 2; i++)
    {
        cin >> A[i] >> B[i] >> C[i] >> K[i];
        A[i]--; B[i]--; C[i]--; K[i]--;
        conn[sortedpair(A[i], B[i])].push_back(i);
        conn[sortedpair(B[i], C[i])].push_back(i);
        conn[sortedpair(C[i], A[i])].push_back(i);
        S[K[i]]++;
    }
    static vector<uint32_t> graph[MAX];
    for(auto k : conn)
    {
        const vector<uint32_t>& v = k.second;
        for(uint32_t i = 0; i < v.size(); i++)
          for(uint32_t j = i+1; j < v.size(); j++)
        {
            graph[v[i]].push_back(v[j]);
            graph[v[j]].push_back(v[i]);
        }
    }
    static uint32_t graphidx[MAX], of_preorder[MAX],
                    preorder[MAX], postorder[MAX];
    uint32_t order = 1;
    static bitset<MAX> vis;
    stack<uint32_t> tovis;
    tovis.push(0); vis[0] = true;
    while(not tovis.empty())
    {
        uint32_t u = tovis.top();
        uint32_t& i = graphidx[u];
        for(; i < graph[u].size(); i++)
        {
            uint32_t v = graph[u][i];
            if(not vis[v])
            {
                tovis.push(v);
                vis[v] = true;
                of_preorder[order] = v;
                preorder[v] = order++;
                break;
            }
        }
        if(i == graph[u].size())
            postorder[u] = order, tovis.pop();
    }
    static query_t queries[MAX];
    for(uint32_t i = 1; i < n - 2; i++)
        queries[i-1] = query_t{preorder[i], postorder[i]-1, i};
    sort(queries, queries + (n-3), mo_cmp);
    static uint32_t T[MAX];
    uint32_t a = -1u, b = -1u;
    uint32_t u = 0, r = 0;
    for(uint32_t qi = 0; qi < n - 3; qi++)
    {
        uint32_t x, y, _; tie(x, y, _) = queries[qi];
        if(a == -1u and b == -1u)
        {
            a = x; b = y;
            for(uint32_t i = a; i <= b; i++)
            {
                NOTE_ADD(of_preorder[i]);
            }
        }
        else
        {
            while(b < y)
            {
                b++;
                NOTE_ADD(of_preorder[b]);
            }
            while(a < x)
            {
                NOTE_REMOVE(of_preorder[a]);
                a++;
            }
            while(a > x)
            {
                a--;
                NOTE_ADD(of_preorder[a]);
            }
            while(b > y)
            {
                NOTE_REMOVE(of_preorder[b]);
                b--;
            }
        }
        if(u == 0)
            r++;
    }
    cout << r;
}
