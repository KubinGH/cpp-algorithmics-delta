#include <bits/stdc++.h>

using namespace std;

uint32_t memo[][2] = {
    {4, 0}, {8, 2}, {24, 4}, {90, 6},
    {114, 12}, {524, 16}, {888, 18},
    {1130, 20}, {1328, 32}, {9552, 34},
    {15684, 42}, {19610, 50}, {31398, 70},
    {155922, 84}, {360654, 94}, {370262, 110},
    {492114, 112}, {1349534, 116}, {1357202, 130},
    {2010734, 146}, {4652354, 152}, {17051708, 178},
    {20831324, 208}, {47326694, 218}, {122164748, 220},
    {189695660, 232}, {191912784, 246}
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    reverse(begin(memo), end(memo));
    for(uint32_t i = 0; i < sizeof(memo) / 8 - 1; i++)
    {
        uint32_t a = memo[i][0], b = memo[i][0] + memo[i][1];
        if(n >= b)
        {
            cout << a << " " << b;
            return 0;
        }
        else if(n >= a and n - a > memo[i+1][1])
        {
            cout << a << " " << n;
            return 0;
        }
    }
    cout << "4 4" << endl;
}
