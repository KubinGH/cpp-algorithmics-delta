#include <bits/stdc++.h>
#define MAX 1000000
#define ABS_DIFF(a, b) ((a) > (b) ? (a) - (b) : (b) - (a))

using namespace std;

typedef unsigned int uint32_t;

int main()
{
    uint32_t n;
    cin >> n;
    static char buffer[MAX+1];
    cin >> buffer;
    static bool tree_type[MAX];
    for(uint32_t i = 0; i < n; i++)
        tree_type[i] = buffer[i] == 'S';
    static uint32_t R[MAX][2];
    R[0][0] = tree_type[0] == 0; R[0][1] = tree_type[0] == 1;
    for(uint32_t i = 1; i < n; i++)
    {
        R[i][0] = R[i-1][0]; R[i][1] = R[i-1][1];
        if(tree_type[i] == 0)
            R[i][0]++;
        else
            R[i][1]++;
    }
    uint32_t i, j;
    for(i = 1; i < n - 2; i++)
    {
        int32_t d1 = R[i-1][0] - R[i-1][1];
        for(j = i + 2; j < n - 1; j++)
        {
            int32_t d2 = R[j-1][0] - R[i][0] - R[j-1][1] + R[i][1];
            int32_t d3 = R[n-1][0] - R[j][0] - R[n-1][1] + R[j][1];
            if(d1 == d2 and d2 == d3)
                goto found;
        }
    }
    cout << "BRAK";
    return 0;
found:
    cout << i + 1 << " " << j + 1;
}
