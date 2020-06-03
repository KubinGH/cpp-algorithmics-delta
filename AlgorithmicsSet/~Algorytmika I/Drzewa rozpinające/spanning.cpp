#include <iostream>
#include <ktl/math/gaussian_elimination.cpp>
#include <ktl/math/modular.cpp>

using namespace std;

using cmint = mint<uint, uint(1e9+9)>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n, m;
    cin >> n >> m;
    vector<vector<cmint>> M(n-1, vector<cmint>(n-1));
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        if(u<n-1) M[u][u]++;
        if(v<n-1) M[v][v]++;
        if(u<n-1 and v<n-1) M[u][v]--, M[v][u]--;
    }
    cout << determinant(M);
}
