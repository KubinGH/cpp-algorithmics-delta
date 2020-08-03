#include <bits/stdc++.h>

using namespace std;

vector<size_t> prefixoprefixes(const string& S)
{
    const size_t n = S.size();
    vector<size_t> Z(n);
    for(size_t i = 1, L = 0, R = 0; i < n; i++)
    {
        if(i < R)
            Z[i] = min(Z[i-L], R-i);
        while(S[Z[i]] == S[i+Z[i]])
            Z[i]++;
        if(R <= i + Z[i])
            L = i, R = i + Z[i];
    }
    return Z;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    string S;
    cin >> S;
    const size_t n = S.size();
    size_t m;
    cin >> m;

    if(m > n)
    {
        cout << "-1" << endl;
        return 0;
    }

    auto Z = prefixoprefixes(S);

    vector<vector<int>> reach(m+1, vector<int>(n+1, -1));
    vector<vector<pair<int, size_t>>> ops(n+1);

    auto process_ops = [&](vector<int>& vec) {
        int v = -1;
        size_t r = 0;
        for(size_t i = 0; i <= n; i++)
        {
            for(auto p : ops[i])
                if(p.second > r)
                    tie(v, r) = p;
            ops[i].clear();
            vec[i] = i < r ? v : -1;
        }
    };
    reach[0][0] = 0;

    vector<string> spec(m);
    vector<char> A(m);
    vector<size_t> B(m);

    bool run_process = false;
    for(size_t j = 0; j < m; j++)
    {
        char t;
        cin >> t;

        if(run_process)
            process_ops(reach[j]);
        run_process = false;

        if(t == 'A')
        {
            cin >> A[j];
            spec[j] = string("A ") + A[j];
            for(size_t i = 0; i < n; i++)
              if(reach[j][i] != -1)
            {
                if(S[i] == A[j])
                    reach[j+1][i+1] = i;
            }
        }
        else if(t == 'B')
        {
            cin >> B[j];
            spec[j] = string("B ") + to_string(B[j]);
            for(size_t i = B[j]; i+B[j] <= n; i++)
              if(reach[j][i] != -1)
            {
                if(B[j] <= Z[i])
                    reach[j+1][i+B[j]] = i;
            }
        }
        else
        {
            for(size_t i = 0; i < n; i++)
              if(reach[j][i] != -1)
            {
                size_t p = max((size_t)1, min({i, n - i, Z[i]}));
                ops[i+1].emplace_back(i, i+p+1);
            }
            run_process = true;
        }
    }
    if(run_process)
        process_ops(reach[m]);

    if(reach[m][n] != -1)
    {
        vector<string> result(m);
        size_t i = n;
        for(size_t j = m; j --> 0; )
        {
            assert(reach[j+1][i] != -1);
            assert(i > 0);
            if(spec[j].empty())
            {
                size_t i1 = reach[j+1][i];
                if(i - i1 == 1)
                    result[j] = string("A ") + S[i1];
                else
                    result[j] = string("B ") + to_string(i - i1);
                i = i1;
            }
            else
            {
                result[j] = spec[j];
                i -= spec[j][0] == 'A' ? 1 : B[j];
            }
        }
        assert(i == 0);

        cout << m << '\n';
        for(size_t j = 0; j < m; j++)
            cout << result[j] << '\n';
    }
    else
    {
        cout << "-1" << endl;
    }
}
