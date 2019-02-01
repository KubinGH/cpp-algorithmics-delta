#include <bits/stdc++.h>

using namespace std;

typedef tuple<uint32_t, uint32_t, uint32_t, uint32_t> dt;

const size_t MAX = 100000;

int main()
{
    uint32_t n, k;
    cin >> n >> k;
    static array<uint64_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    sort(A.begin(), A.begin() + n);
    uint32_t d = 1;
    priority_queue<dt, vector<dt>, greater<dt> > Q;
    set<dt> S;
    Q.emplace(A[0]+A[0]+A[0], 0, 0, 0);
    dt c;
    while(not Q.empty())
    {
        c = Q.top(); Q.pop();
        if(S.find(c) != S.end())
            continue;
        else
            S.insert(c);
        if(d == k)
            break;
        else
            d++;
        uint32_t i = get<1>(c), j = get<2>(c), l = get<3>(c);
        if(i < n - 1) Q.emplace(A[i+1]+A[j]+A[l], i+1, j, l);
        if(j < n - 1) Q.emplace(A[i]+A[j+1]+A[l], i, j+1, l);
        if(l < n - 1) Q.emplace(A[i]+A[j]+A[l+1], i, j, l+1);
    }
    cout << get<0>(c);
}
