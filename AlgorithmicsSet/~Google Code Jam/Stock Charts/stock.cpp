#include <ktl/graph/bipartite_matching.cpp>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t T;
    cin >> T;

    for(size_t no = 1; no <= T; no++)
    {
        size_t n, k;
        cin >> n >> k;

        vector<vector<uint>> A(n, vector<uint>(k));
        for(auto& row : A)
            for(auto& a : row)
                cin >> a;

        auto ok = [&](size_t u, size_t v) {
            for(size_t i = 0; i < k; i++)
                if(A[u][i] >= A[v][i])
                    return false;
            return true;
        };

        vector<vector<size_t>> graph(2*n);
        for(size_t u = 0; u < n; u++)
            for(size_t v = 0; v < n; v++)
                if(ok(u, v))
                    graph[u].push_back(v+n), graph[v+n].push_back(u);

        auto match = bipartite_matching{graph}();
        auto result = count(match.begin(), match.begin() + n, SIZE_MAX);

        cout << "Case #" << no << ": " << result << endl;
    }
}
