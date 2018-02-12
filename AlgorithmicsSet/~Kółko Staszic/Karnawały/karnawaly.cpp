#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int uint64_t;

const uint64_t HOUR_S = 60 * 60;
const uint64_t DAY_H = 24;
const uint64_t YEAR_D = 365;

int main()
{
    uint64_t x, y, n;
    cin >> x >> y >> n;
    uint64_t d = x * y, p = n + 1;
    uint64_t seconds = 1, hours = 0, days = 0, years = 0;
    for(uint64_t i = 0; i < d; i++)
    {
        seconds *= p; hours *= p; days *= p; years *= p;
        hours += seconds / HOUR_S; seconds %= HOUR_S;
        days += hours / DAY_H; hours %= DAY_H;
        years += days / YEAR_D; days %= YEAR_D;
        cout << years << " " << days << " " << hours << " " << seconds << endl;
    }
}
