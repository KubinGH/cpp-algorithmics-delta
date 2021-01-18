#include <bits/stdc++.h>

using namespace std;

template<typename Ctr>
Ctr reversed(const Ctr& c) { return Ctr(c.rbegin(), c.rend()); }

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

vector<vector<vector<size_t>>> splitarr(string A, string B)
{
    const size_t n = A.size(), m = B.size();


    vector<vector<vector<size_t>>> res(m+1, vector<vector<size_t>>(n+1, vector<size_t>(m+1)));
    for(size_t j = 0; j <= m; j++) // up
    {
        for(size_t i = 0; i <= n; i++) // left
        {
            auto curr = lcs_array(A, B, rect{{{i, n}, {j, m}}});
            for(size_t k = j; k <= B.size(); k++)
                res[j][i][k] = curr[n - i][k - j];
        }
    }
    return res;
}

void divida_et_impera(string A, string B, vector<query> queries, vector<size_t>& out)
{
    const size_t n = A.size(), m = B.size();
    if(queries.empty())
        return;
    if(n <= 4 and m <= 4)
    {
        for(auto [i, pos] : queries)
            out[i] = lcs(A, B, pos);
        return;
    }
    if(A.size() < B.size())
    {
        for(auto& [i, pos] : queries)
            swap(pos[0], pos[1]);
        return divida_et_impera(B, A, queries, out);
    }

    const size_t mid = A.size() / 2;

    auto A_left = A.substr(0, mid), A_right = A.substr(mid);

    vector<query> left, right;
    {
        auto L = splitarr(A_left, B), R = splitarr(reversed(A_right), reversed(B));
        reverse(R.begin(), R.end());
        for(size_t j = 0; j <= m; j++)
        {
            reverse(R[j].begin(), R[j].end());
            for(size_t i = 0; i <= n-mid; i++)
                reverse(R[j][i].begin(), R[j][i].end());
        }

        for(auto que : queries)
        {
            const auto& [qi, pos] = que;
            if(pos[0][1] <= mid)
                left.push_back(que);
            else if(pos[0][0] >= mid)
            {
                right.push_back(que);
                right.back().pos[0][0] -= mid;
                right.back().pos[0][1] -= mid;
            }
            else
            {
                const size_t j1 = pos[1][0], j2 = pos[1][1], i1 = pos[0][0], i2 = pos[0][1];
                for(size_t k = pos[1][0]; k < pos[1][1]; k++)
                    out[qi] = max(out[qi], L[j1][i1][k] + R[j2][i2-mid][k]);
            }
        }
    }

    divida_et_impera(A_left,  B, left,  out);
    divida_et_impera(A_right, B, right, out);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, q;
    cin >> n >> m >> q;

    string A, B;
    cin >> A >> B;

    vector<query> queries(q);
    for(auto& [i, p] : queries)
        cin >> p[0][0] >> p[0][1] >> p[1][0] >> p[1][1], p[0][0]--, p[1][0]--;
    for(size_t i = 0; i < q; i++)
        queries[i].i = i;

    vector<size_t> out(q);
    divida_et_impera(A, B, queries, out);

    for(size_t i = 0; i < q; i++)
        cout << out[i] << '\n';
}
