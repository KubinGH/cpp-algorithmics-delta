#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <iostream>

using namespace std;

bool check_solution(const vector<uint32_t>& A, const vector<bool>& R)
{
    uint32_t n = A.size(), lo = 1;
    stack<uint32_t> X, Y;
    X.push(n+1); Y.push(n+2);
    for(uint32_t i = 0; i < n; i++)
    {
        if(R[i] == 0)
            X.push(A[i]);
        else
            Y.push(A[i]);
        while(lo <= n and (X.top() == lo or Y.top() == lo))
        {
            if(X.top() == lo) X.pop();
            if(Y.top() == lo) Y.pop();
            lo++;
        }
    }
    return X.size() == 1 and Y.size() == 1;
}

pair<bool, vector<bool>> solve(const vector<uint32_t>& A)
{
    uint32_t n = A.size();
    vector<uint32_t> I(n);
    for(uint32_t i = 0; i < n; i++)
        cerr << A[i] << " ", I[A[i]-1] = i; cerr << endl;
    vector<uint32_t> L(n);
    uint32_t m = 0;
    for(uint32_t a = 0; a < n; a++)
    {
        uint32_t i = I[a];
        L[i] = max(m, i);
        m = max(m, L[i]);
    }
    vector<vector<uint32_t>> G(n);
    set<pair<uint32_t, uint32_t>> V;
    bool ok = true;
    for(uint32_t i = 0; i < n and ok; i++)
    {
        while(not V.empty() and i > V.begin()->first)
            V.erase(V.begin());
        vector<decltype(V)::iterator> td;
        for(auto it = V.begin(); it != V.end(); it++)
        {
            uint32_t j = I[it->second];
            if(L[j] < L[i] or (L[i] == L[j] and A[j] < A[i]))
            {
                G[i].push_back(j), G[j].push_back(i);
                cerr << i << " -> " << j << endl;
                td.push_back(it);
            }
            else
                break;
        }
        for(auto it : td) V.erase(it); td.clear();
        V.emplace(L[i], A[i]-1);
    }
    vector<bool> R(n), vis(n);
    queue<uint32_t> Q;
    for(uint32_t i = 0; i < n and ok; i++)
    {
        if(vis[i]) continue;
        vis[i] = true; Q.push(i); R[i] = 0;
        while(not Q.empty())
        {
            uint32_t u = Q.front(); Q.pop();
            for(uint32_t v : G[u])
            {
                if(not vis[v])
                    R[v] = !R[u], vis[v] = true, Q.push(v);
                else if(R[u] == R[v])
                {
                    ok = false;
                    break;
                }
            }
        }
    }
    return {check_solution(A, R), R};
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<uint32_t> A(n);
    for(uint32_t i = 0; i < n; i++) cin >> A[i];
    auto r = solve(A);
    if(r.first)
    {
        cout << "TAK\n";
        for(uint32_t b : r.second)
            cout << uint32_t(b)+1 << " ";
    }
    else
        cout << "NIE";
}
