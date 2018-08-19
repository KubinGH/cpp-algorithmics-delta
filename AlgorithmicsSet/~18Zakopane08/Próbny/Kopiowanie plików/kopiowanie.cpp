#include <bits/stdc++>h>

using namespace std;

const size_t MAX = 512;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, a, b;
    cin >> n >> a >> b;
    static bool A[MAX][MAX];
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        cin >> u >> v;
        A[u][v] = A[v][u] = true;
    }
    static uint32_t P[MAX];
    for(uint32_t i = 0; i < n; i++)
        cin >> P[i];
    static bitset<MAX> Q;
    uint32_t r = n - 2;
    do {
        Q.reset();
        Q[a] = Q[b] = true;
        for(uint32_t )
    } while(next_permutation(P, P + n));
    cout << r;
}
