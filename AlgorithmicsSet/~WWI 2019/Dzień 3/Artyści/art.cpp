#include <bits/stdc++.h>

using namespace std;

template<typename Arg, typename Function>
Arg partition_index(Arg lo, Arg hi, Function f)
{
    while(lo < hi)
    {
        auto mid = (lo + hi) / 2;
        if(f(mid))
            hi = mid;
        else
            lo = mid+1;
    }
    return lo;
}

template<typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

int64_t sigma(int64_t x)
{
    return x * (x + 1) / 2;
}
int64_t isigma(int64_t s)
{
    int64_t x = floor(0.5 * (sqrt(8*s + 1) - 1));
    return x;
}

struct plank
{
    int64_t h, x, y;

    int64_t quantile(int64_t k)
    {
        auto i = isigma(k);
        auto s = sigma(x);
        if(k < 0 or (x+1)*(y+1) <= k)
            return INT64_MAX;
        else if(i <= x)
            return (i+1) * h;
        else if(k <= (x+1)*(y+1) - s)
            return (x+1+(k-s)/(x+1)) * h;
        else
            return h * (x+y+2) - quantile((x+1)*(y+1)-1 - k);
    }

    int64_t count_le(int64_t a)
    {
        a = min(a - a%h, h * (x+y+1));
        if(a < 0)
            return 0;
        else if(a > h*y)
            return (x+1)*(y+1) - count_le(h*(x+y+1) - a);
        int64_t r = 0, aa = a/h;
        r += sigma(min(aa, x));
        if(aa > x)
            r += (x+1) * (min(aa, y) - x);
        return r;
    }

    int64_t count_lt(int64_t a) { return count_le(a - 1); }
};

template<typename Iterator, typename Compare>
vector<size_t> lesser_to_left(Iterator first, Iterator last, Compare c)
{
    vector<size_t> pot;
    pot.reserve(distance(first, last));
    stack<pair<int, size_t>> st;
    for(size_t i = 0; first != last; ++first, i++)
    {
        auto curr = *first;
        while(not st.empty() and c(st.top().first, curr))
            st.pop();
        pot.push_back(st.empty() ? SIZE_MAX : st.top().second);
        st.emplace(curr, i);
    }
    return pot;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n; int64_t L, R;
    cin >> n >> L >> R;

    vector<int> H(n+2);
    vector<plank> planks(n+2);
    for(size_t i = 1; i <= n; i++)
    {
        cin >> H[i];
        planks[i].h = H[i];
    }

    auto left_ltl = lesser_to_left(H.begin(), H.end(), greater_equal<int>()),
         right_ltl = lesser_to_left(H.rbegin(), H.rend(), greater<int>());
    reverse(right_ltl.begin(), right_ltl.end());
    for(size_t i = 1; i <= n; i++)
    {
        left_ltl[i]++;
        right_ltl[i] = n - right_ltl[i];
    }

    for(size_t i = 1; i <= n; i++)
        tie(planks[i].x, planks[i].y) = minmax(i - left_ltl[i], right_ltl[i] - i);

    L--;
    const size_t m = R - L;

    int64_t aL = partition_index<int64_t>(1, 1e15, [&](int64_t a) {
        int64_t r = 0;
        for(size_t i = 1; i <= n; i++)
            r += planks[i].count_lt(a);
        return r > L;
    }) - 1;

    int64_t to_skip = L;
    for(size_t i = 1; i <= n; i++)
        to_skip -= planks[i].count_lt(aL);

    min_priority_queue<pair<int64_t, size_t>> Q;

    vector<int64_t> index(n+2);

    for(size_t i = 1; i <= n; i++)
    {
        auto p = planks[i];
        int64_t c = p.count_lt(aL);
        Q.emplace(p.quantile(c), i);
        index[i] = c;
    }

    vector<int64_t> a;
    a.reserve(m);
    while(a.size() < m)
    {
        auto q = Q.top(); Q.pop();
        int64_t e; size_t i;
        tie(e, i) = q;
        if(to_skip) to_skip--;
        else a.push_back(e);
        Q.emplace(planks[i].quantile(++index[i]), i);
    }

    for(auto e : a)
        cout << e << " ";
}
