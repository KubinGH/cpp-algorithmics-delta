#include <bits/stdc++.h>

using namespace std;

constexpr int M = 1 << 20;
int A[M], D[M];

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int x; cin >> x;
    while(cin >> x) A[x]++;

    for(int d = 1; d < M; d++)
    {
        D[d] += A[d];
        for(int e = 2*d; e < M; e += d)
            D[e] = max(D[e], D[d]);
    }

    cout << *max_element(D, D + M);
}
