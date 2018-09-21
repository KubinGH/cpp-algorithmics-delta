#include <bits/stdc++.h>

using namespace std;

bool is_leap_year(uint32_t y)
{
    return y%4 == 0 and not (y%100 == 0 and y%400 != 0);
}

int main()
{
    uint32_t d, m, y;
    cin >> d >> m >> y;
    uint32_t daycount[13] = {
        0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };
    if(is_leap_year(y))
        daycount[2]++;
    cout << ((1 <= d and d <= daycount[m]) ? "TAK" : "NIE");
}
