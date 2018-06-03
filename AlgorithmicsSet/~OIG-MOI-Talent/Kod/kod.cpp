#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000;

typedef unsigned int uint32_t;

int main()
{
    uint32_t n;
    cin >> n;
    static uint32_t A[MAX], P[MAX];
    fill(A, A + n, 1);
    for(uint32_t i = 0; i < n - 2; i++)
    {
        cin >> P[i]; P[i]--;
        A[P[i]]++;
    }
    priority_queue<uint32_t, vector<uint32_t>, greater<uint32_t> > T;
    for(uint32_t i = 0; i < n; i++)
        if(A[i] == 1)
            T.push(i);
    vector<pair<uint32_t, uint32_t> > E;
    for(uint32_t i = 0; i < n - 2; i++)
    {
        uint32_t t = T.top(); T.pop();
        E.push_back(make_pair(t, P[i]));
        if(E.back().first > E.back().second)
            swap(E.back().first, E.back().second);
        A[P[i]]--;
        if(A[P[i]] == 1)
            T.push(P[i]);
    }
    uint32_t t1 = T.top(); T.pop(); uint32_t t2 = T.top();
    E.push_back(make_pair(t1, t2));
    sort(E.begin(), E.end());
    for(uint32_t i = 0; i < n - 1; i++)
        cout << E[i].first+1 << " " << E[i].second+1 << "\n";
}
