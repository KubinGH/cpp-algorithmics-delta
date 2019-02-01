#include <bits/stdc++.h>

using namespace std;

const size_t N = 20;

int main()
{
    uint32_t n;
    cin >> n;
    static long double Q[N/5][N/5][N/5][N/5][N/5];
    uint32_t percent[5];
    for(uint32_t i = 0; i < 5; i++)
    {
        char _, a, b;
        cin >> _ >> _ >> a >> b;
        if(a == '0')
            percent[i] = b - '0';
        else
            percent[i] = (b - '0') + 10*(a - '0');
    }
    #define range(__i, __lo, __hi) for((__i) = (__lo); (__i) < (__hi); (__i)++)
    uint32_t j[5];
    Q[0][0][0][0][0] = 1;
    range(j[0], 0, n/5+1)
      range(j[1], 0, n/5+1)
        range(j[2], 0, n/5+1)
          range(j[3], 0, n/5+1)
            range(j[4], 0, n/5+1)
    {
        long double& q = Q[j[0]][j[1]][j[2]][j[3]][j[4]];
        if(j[0]) q += percent[0] * Q[j[0]-1][j[1]][j[2]][j[3]][j[4]];
        if(j[1]) q += percent[1] * Q[j[0]][j[1]-1][j[2]][j[3]][j[4]];
        if(j[2]) q += percent[2] * Q[j[0]][j[1]][j[2]-1][j[3]][j[4]];
        if(j[3]) q += percent[3] * Q[j[0]][j[1]][j[2]][j[3]-1][j[4]];
        if(j[4]) q += percent[4] * Q[j[0]][j[1]][j[2]][j[3]][j[4]-1];
        q /= 100;
    }
    double q = Q[n/5][n/5][n/5][n/5][n/5];
    cout << fixed << setprecision(10);
    if(isnan(q))
        cout << 0.0;
    else
        cout << q;
}
