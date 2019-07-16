#include <bits/stdc++.h>

using namespace std;

struct calendar_t
{
    vector<size_t> days_in_month, days_until_month;
    calendar_t(const vector<size_t>& d) : days_in_month(d), days_until_month(d.size() + 1)
    {
        partial_sum(d.begin(), d.end(), days_until_month.begin() + 1);
    }

    size_t days_until(size_t day, size_t month) const
    {
        return days_until_month[month] + day;
    }
    pair<size_t, size_t> day_month_after(size_t days) const
    {
        auto month = prev(upper_bound(days_until_month.begin(), days_until_month.end(), days)) - days_until_month.begin();
        return {days - days_until_month[month], month};
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<size_t> a(n), b(m);
    for(size_t i = 0; i < n; i++)
        cin >> a[i];
    for(size_t i = 0; i < m; i++)
        cin >> b[i];

    calendar_t A(a), B(b);

    size_t q;
    cin >> q;
    while(q --> 0)
    {
        size_t day, month; char c;
        cin >> day >> month >> c; day--; month--;
        auto& c_from = (c == 'A' ? A : B);
        auto& c_to   = (c == 'A' ? B : A);
        auto p = c_to.day_month_after(c_from.days_until(day, month));
        auto day1 = p.first, month1 = p.second;
        cout << day1+1 << " " << month1+1 << endl;
    }
}
