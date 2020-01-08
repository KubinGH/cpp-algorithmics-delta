#include <bits/stdc++.h>

using namespace std;

template<typename Fun, int Count = 10>
int periodical(int value, Fun f, int64_t times)
{
    if(times <= 0)
        return value;
    int got[Count];
    for(int x = 0; x < Count; x++)
        got[x] = -1;

    got[value] = 0;
    int x = value, watch, period = 0, since = -1;
    vector<int> cache = {x};
    for(watch = 1; watch < 2*Count; watch++)
    {
        cache.push_back(x = f(x));
        if(got[x] != -1)
        {
            period = watch - got[x];
            since = got[x];
            break;
        }
        got[x] = watch;
    }

    return times <= since ? cache[times] : cache[(times - since)%period + since];
}

string solve_r(int64_t a, int64_t b, int64_t u, int64_t v, int64_t p,
               array<array<int, 10>, 10> op)
{
    if(a == 0 and b == 0) return "";

    int t = a % 10;

    #define Apply(_var_, _val_, _times_) \
        _var_ = periodical(_var_, [&](int _par_) { return op[_par_][_val_]; }, _times_)

    if(a == b)
        Apply(t, a%10, v-u);
    else
    {
        Apply(t, a%10, p-u-1);

        if(a/10 == b/10)
            for(int d = a%10 + 1; d < b%10; d++)
                Apply(t, d, p);
        else
        {
            for(int d = a%10 + 1; d < 10; d++)
                Apply(t, d, p);

            t = periodical(t, [&](int x) {
                for(int d = 0; d < 10; d++)
                    Apply(x, d, p);
                return x;
            }, b/10-a/10-1);

            for(int d = 0; d < b%10; d++)
                Apply(t, d, p);
        }

        Apply(t, b%10, v+1);
    }
    return solve_r(a/10, b/10, u+(a%10)*p, v+(b%10)*p, p*10, op) + char('0' + t);

    #undef Apply
}

string solve(int64_t a, int64_t b, array<array<int, 10>, 10> op)
{
    auto result = solve_r(a, b, 0, 0, 1, op);
    while(result.size() > 1 and result.front() == '0')
        result.erase(result.begin());
    return result;
}

int main()
{
    array<array<int, 10>, 10> op;
    for(size_t x = 0; x < 10; x++)
        for(size_t y = 0; y < 10; y++)
            cin >> op[x][y];

    int64_t a, b;
    cin >> a >> b;

    cout << solve(a, b, op);
}
