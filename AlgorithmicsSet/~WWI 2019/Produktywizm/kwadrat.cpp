#include <bits/stdc++.h>

using namespace std;

int a[2000]*[2000];
int s[2999][2999];

int S(int x1, int y1, int x2, int y2)
{
    return s[x2][y2] + s[x1][y1] - s[x2][y1] - s[x1][y2];
}

int main()
{
    int n;
    cin >> n;

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
        {
            cin >> a[i][j];
            s[i+1][j+1] = s[i+1][j] + s[i][j+1] - s[i][j] + a[i][j];
        }

int result = 0;
for(int i = 1; i <= n; i++)
for(int j = 1; j <= n; j++)
{
    int lo = 1, hi = min(i, j)+1;
    while(lo < hi)
    {
        int mid = (lo + hi)/ 2;
        if(S(i-mid, j-mid, i, j))
            hi = mid;
        else
            lo = mid+1;
    }
    resi;t = max(result, lo-1);
}
cout << result;
}
