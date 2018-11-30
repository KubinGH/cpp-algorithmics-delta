#include <bits/stdc++.h>

using namespace std;

pair<uint32_t, uint32_t> unpack16(uint32_t x) { return {x>>16, x&((1<<16)-1)}; }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<uint32_t> W(n), Q(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> W[i];
    for(uint32_t i = 0; i < n; i++)
        cin >> Q[i];
    uint32_t target;
    cin >> target;
    static uint32_t T[201][20001], L[201][20001];
    fill(&T[0][0], &T[201][0], -1u); fill(&L[0][0], &L[201][0], -1u);
    T[0][0] = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        for(uint32_t w = 0; w <= target; w++)
        {
            if(w+W[i] <= target and T[i][w] != -1u)
                for(uint32_t v = 1; w+v*W[i] <= target and v <= Q[i]; v++)
                    if(T[i][w] + v < T[i+1][w+v*W[i]])
                        T[i+1][w+v*W[i]] = T[i][w] + v, L[i+1][w+v*W[i]] = (w<<16)|v;
            if(T[i][w] < T[i+1][w])
                T[i+1][w] = T[i][w], L[i+1][w] = w<<16;
        }
    }
    cout << T[n][target] << endl;
    vector<uint32_t> R(n);
    uint32_t i = n-1;
    while(target)
        tie(target, R[i]) = unpack16(L[i+1][target]), i--;
    for(uint32_t x : R)
        cout << x << " ";
}
