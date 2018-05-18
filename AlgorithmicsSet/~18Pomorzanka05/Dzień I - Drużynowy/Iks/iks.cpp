#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    uint32_t x = 0, y = n-1;
    for(uint32_t i = 0; i < n; i++)
    {
        for(uint32_t j = 0; j < n; j++)
        {
            if(j == x or j == y)
                cout << 'X';
            else
                cout << '.';
        }
        cout << '\n';
        x++, y--;
    }
}
