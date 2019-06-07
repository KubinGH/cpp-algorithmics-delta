#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n;
    cin >> n;
    vector<int64_t> A(n);
    for(size_t i = 0; i < n; i++)
        cin >> A[i];

    vector<vector<int64_t>> Q(n+1, vector<int64_t>(n+2, INT64_MIN));
    vector<vector<int>> B(n+1, vector<int>(n+2));

    Q[0][0] = 0;
    for(size_t i = 1; i <= n; i++)
    {
        for(size_t k = 0; k <= i; k++)
        {
            auto a = Q[i-1][k];
            auto b = k>0 ? Q[i-1][k-1] - A[i-1] : INT64_MIN;
            auto c = Q[i-1][k+1] + A[i-1];
            Q[i][k] = max({a, b, c});
            if(Q[i][k] == a)
                B[i][k] = 0;
            else if(Q[i][k] == b)
                B[i][k] = 1;
            else if(Q[i][k] == c)
                B[i][k] = -1;
        }
    }
    cout << Q[n][0] << endl;
    stack<int> s;
    for(size_t i = n+1, k = 0; i --> 1; )
    {
        s.push(B[i][k]);
        if(B[i][k] == 1)
            k--;
        else if(B[i][k] == -1)
            k++;
    }
    while(not s.empty())
        cout << s.top() << " ", s.pop();
}
