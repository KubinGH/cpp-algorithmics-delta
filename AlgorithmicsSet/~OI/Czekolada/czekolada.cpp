#include <bits/stdc++.h>

using namespace std;

struct rect_t
{
    uint32_t x1, y1, x2, y2;
};

int main()
{
    uint32_t n, m;
    cin >> n >> m;
    static uint16_t X[1<<10], Y[1<<10];
    for(uint32_t i = 0; i < n-1; i++) cin >> X[i];
    for(uint32_t i = 0; i < m-1; i++) cin >> Y[i];
    static uint16_t U[1<<10][1<<10], V[1<<10][1<<10], A[1<<10][1<<10], B[1<<10][1<<10];
    for(uint32_t i = 0; i <= n; i++)
      for(uint32_t j = i+1; j <= n; j++)
    {
        U[i][j] = U[i][j-1]; A[i][j] = A[i][j-1];
        if(X[j-1] > U[i][j])
            U[i][j] = X[j-1], A[i][j] = j-1;
    }
    for(uint32_t i = 0; i <= m; i++)
      for(uint32_t j = i+1; j <= m; j++)
    {
        V[i][j] = V[i][j-1]; B[i][j] = B[i][j-1];
        if(Y[j-1] > V[i][j])
            V[i][j] = Y[j-1], B[i][j] = j-1;
    }
    uint32_t r = 0;
    stack<rect_t> S; S.push({0, 0, n-1, m-1});
    while(not S.empty())
    {
        rect_t t = S.top(); S.pop();
        if(t.x1 == t.x2 and t.y1 == t.y2) {}
        else if((t.y1 == t.y2) or (t.x1 < t.x2 and U[t.x1][t.x2] > V[t.y1][t.y2]))
        {
            r += U[t.x1][t.x2];
            S.push({t.x1, t.y1, A[t.x1][t.x2], t.y2});
            S.push({A[t.x1][t.x2]+1, t.y1, t.x2, t.y2});
        }
        else if(t.y1 < t.y2)
        {
            r += V[t.y1][t.y2];
            S.push({t.x1, t.y1, t.x2, B[t.y1][t.y2]});
            S.push({t.x1, B[t.y1][t.y2]+1, t.x2, t.y2});
        }
    }
    cout << r;
}
