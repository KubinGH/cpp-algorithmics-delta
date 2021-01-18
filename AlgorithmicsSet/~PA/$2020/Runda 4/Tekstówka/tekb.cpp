
#include <bits/stdc++.h>

using namespace std;

using rect = array<array<size_t, 2>, 2>;
struct query
{
    size_t i;
    rect pos;
};

vector<vector<size_t>> lcs_array(const string& A, const string& B, rect pos)
{
    const size_t n = pos[0][1]-pos[0][0], m = pos[1][1]-pos[1][0];
    vector<vector<size_t>> L(n+1, vector<size_t>(m+1));
    for(size_t i = 0; i < n; i++)
        for(size_t j = 0; j < m; j++)
            L[i+1][j+1] = max(max(L[i][j+1], L[i+1][j]), L[i][j] + (A[pos[0][0]+i] == B[pos[1][0]+j]));
    return L;
}
size_t lcs(const string& A, const string& B, rect pos)
{
    return lcs_array(A, B, pos)[pos[0][1]-pos[0][0]][pos[1][1]-pos[1][0]];
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, q;
    cin >> n >> m >> q;

    string A, B;
    cin >> A >> B;

    while(q --> 0)
    {
        rect p;
        cin >> p[0][0] >> p[0][1] >> p[1][0] >> p[1][1], p[0][0]--, p[1][0]--;
        cout << lcs(A, B, p) << '\n';
    }
}
