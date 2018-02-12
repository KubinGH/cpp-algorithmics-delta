#include <bits/stdc++.h>
#define MAX 30000

using namespace std;

typedef unsigned short int uint16_t;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    static bool used_col[MAX], used_row[MAX];
    uint16_t n;
    cin >> n;
    uint16_t result = 0;
    for(uint16_t i = 0; i < n; i++)
    {
        uint16_t x, y;
        cin >> x >> y; x--; y--;
        if(not (used_col[x] or used_row[y]))
        {
            used_col[x] = used_row[y] = true;
            result++;
        }
    }
    cout << result;
}
