#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000;

template<typename T>
void uprint(T o)
{
    cerr << o;
}

template<typename A, typename B>
void uprint(pair<A, B> p)
{
    cerr << "(" << p.first << ", " << p.second << ")";
}

template <typename T, template <typename, typename...> class V, typename... Args>
void uprint(V<T, Args...>& it)
{
    cerr << "{";
    for(T i : it)
        uprint(i), cerr << "; ";
    cerr << "}";
}

template<typename T>
void extend(vector<T>& out, vector<T>& in, bool res = true)
{
    out.insert(out.end(), in.begin(), in.end());
}

int main()
{
    //cerr.setstate(ios_base::failbit);
    uint32_t n, m;
    cin >> n >> m;
    static array<unordered_set<uint32_t>, MAX> graph;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t a, b;
        cin >> a >> b; a--; b--;
        graph[a].insert(b); graph[b].insert(a);
    }
    queue<pair<uint32_t, bool> > Q;
    vector<pair<vector<uint32_t>, vector<uint32_t> > > groups;
    vector<uint32_t> free_assets;
    free_assets.reserve(n);
    unordered_set<uint32_t> S;
    S.reserve(n);
    for(uint32_t i = 0; i < n; i++)
        if(not graph[i].empty())
            S.insert(i);
        else
            free_assets.push_back(i);
    //cerr << "Pre-Free: "; uprint(free_assets); cerr << endl;
    while(not S.empty())
    {
        groups.emplace_back(vector<uint32_t>(), vector<uint32_t>());
        Q.emplace(*S.begin(), 0); S.erase(S.begin());
        groups.back().first.push_back(Q.front().first);
        while(not Q.empty())
        {
            pair<uint32_t, bool> curr = Q.front(); Q.pop();
            for(uint32_t x : graph[curr.first])
            {
                auto it = S.find(x);
                if(it != S.end())
                {
                    S.erase(it);
                    Q.emplace(x, not curr.second);
                    if(curr.second)
                        groups.back().first.push_back(x);
                    else
                        groups.back().second.push_back(x);
                }
            }
        }
        if(groups.back().second.empty())
        {
            extend(free_assets, groups.back().first);
            groups.pop_back();
        }
        else if(groups.back().first.size() > groups.back().second.size())
            swap(groups.back().first, groups.back().second);
    }
    //for(auto p : groups)
    //    uprint(p.first), cerr << ", ", uprint(p.second), cerr << " (" << p.first.size() << ", " << p.second.size() << ")" << endl;
    //cerr << "Free: "; uprint(free_assets); cerr << endl;
    vector<uint32_t> A, B;
    A.reserve(n); B.reserve(n);
    for(auto p : groups)
    {
        if(B.size() < A.size())
        {
            extend(A, p.first);
            extend(B, p.second);
        }
        else
        {
            extend(A, p.second);
            extend(B, p.first);
        }
        //cerr << "Groups(it):" << endl;
        //uprint(A); cerr << endl; uprint(B); cerr << endl;
    }
    uint32_t fi = 0;
    if(not free_assets.empty())
    {
        if(B.size() < A.size())
        {
            uint32_t d = min(A.size() - B.size(), free_assets.size());
            B.insert(B.end(), free_assets.begin() + fi, free_assets.begin() + (fi + d));
            fi += d;
        }
        if(A.size() < B.size())
        {
            uint32_t d = min(B.size() - A.size(), free_assets.size());
            A.insert(A.end(), free_assets.begin() + fi, free_assets.begin() + (fi + d));
            fi += d;
        }
    }
    if(not free_assets.empty())
    {
        A.insert(A.end(), free_assets.begin() + fi, free_assets.begin() + (fi + (free_assets.size() - fi) / 2));
        fi += (free_assets.size() - fi) / 2;
        B.insert(B.end(), free_assets.begin() + fi, free_assets.end());
    }
    uint32_t result = 0;
    for(uint32_t a : A)
        result += B.size() - graph[a].size();
    cout << result;
}
