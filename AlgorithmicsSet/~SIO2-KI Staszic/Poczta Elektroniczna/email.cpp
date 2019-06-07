#include <bits/stdc++.h>
#include <ktl/util/make_vector.cpp>
#include <ktl/util/debug_macros.cpp>

using namespace std;

int main()
{
    size_t n;
    cin >> n;

    vector<int> A;
    while(n --> 0)
    {
        int a;
        cin >> a;
        if(A.empty() or a != A.back())
            A.push_back(a);
    }
    n = A.size();

    for(auto v : A)
        cdbg << v << " ";
    cdbg << endl;

    auto Q = make_vector<int>(n + 1, n + 1);
    for(size_t i = 0; i < n; i++)
        Q[i][i+1] = 1;
    for(size_t d = 2; d <= n; d++)
    {
        for(size_t i = 0, j = i+d; j <= n; i++, j++)
        {
            Q[i][j] = INT_MAX;
            if(A[i] == A[j-1])
                Q[i][j] = Q[i+1][j-1] + 1;
            for(size_t k = i; k < j; k++)
                Q[i][j] = min(Q[i][j], Q[i][k] + Q[k][j]);
            cdbg << i << ".." << j << ": " << Q[i][j] << endl;
        }
    }

    cout << Q[0][n];
}
