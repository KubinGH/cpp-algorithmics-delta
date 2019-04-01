#include <bits/stdc++.h>

using namespace std;

vector<uint32_t> A;
vector<pair<uint32_t, uint32_t>> operations;

void S(uint32_t L, uint32_t R)
{
    vector<uint32_t> B; B.reserve(R - L);
    for(uint32_t i = 1; i < R - L; i += 2)
        B.push_back(A[L + i]);
    for(uint32_t i = 0; i < R - L; i += 2)
        B.push_back(A[L + i]);
    for(uint32_t i = 0; i < R - L; i++)
        A[L + i] = B[i];
    operations.emplace_back(L + 1, R);
}

void S_traverse_to_front(uint32_t L, uint32_t R)
{
    if(L == R)
        return;
    if(R < L+4)
    {
        for(uint32_t i = R; i --> L; )
            S(i, i+2);
    }
    else
    {
        if((R - L) % 2 == 1)
        {
            S(L, R+1);
            S_traverse_to_front(L, (L+R)/2);
        }
        else
        {
            S(L+1, R+1);
            S_traverse_to_front(L+1, (L+R)/2);
            S(L, L+2);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    A.resize(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];

    vector<uint32_t> V = A;
    sort(V.begin(), V.end());
    for(uint32_t i = 0; i < n; i++)
        A[i] = lower_bound(V.begin(), V.end(), A[i]) - V.begin();

    for(uint32_t i = 0; i < n; i++)
        S_traverse_to_front(i, find(A.begin(), A.end(), i) - A.begin());

    cout << operations.size() << "\n";
    for(auto p : operations)
        cout << p.first << " " << p.second << "\n";
}