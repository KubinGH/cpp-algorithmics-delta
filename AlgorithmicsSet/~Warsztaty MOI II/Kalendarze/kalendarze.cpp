#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static array<uint32_t, MAX> A, B;
    static array<uint32_t, MAX> AS, BS;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        if(i > 0) AS[i] = AS[i - 1];
        AS[i] += A[i];
    }
    for(uint32_t i = 0; i < m; i++)
    {
        cin >> B[i];
        if(i > 0) BS[i] = BS[i - 1];
        BS[i] += B[i];
    }
    uint32_t z;
    cin >> z;
    for(uint32_t t = 0; t < z; t++)
    {
        uint32_t days, days_a, months;
        char calendar;
        cin >> days_a >> months >> calendar;
        if(calendar == 'A')
        {
            days = days_a + (months > 1 ? AS[months - 2] : 0);
            uint32_t index = lower_bound(BS.begin(), BS.begin() + m, days) - BS.begin();
            cout << (index ? days - BS[index - 1] : days) << " " << index + 1 << endl;
        }
        else
        {
            days = days_a + (months > 1 ? BS[months - 2] : 0);
            uint32_t index = lower_bound(AS.begin(), AS.begin() + n, days) - AS.begin();
            cout << (index ? days - AS[index - 1] : days) << " " << index + 1 << endl;
        }
    }
}
