#include <bits/stdc++.h>

using namespace std;

struct triple
{
    int first, second, third;

    friend triple operator+ (const triple& a, const triple& b)
    {
        return {a.first+b.first, a.second+b.second, a.third+b.third};
    }

    friend ostream& operator<< (ostream& out, const triple& t)
    {
        return out << "[" << t.first << ", " << t.second << ", " << t.third << "]";
    }

#define INPLACE_ARITHMETIC(__OP, __IOP) \
    triple& operator __IOP (const triple& __other) { return *this = *this __OP __other; }

    INPLACE_ARITHMETIC(+, +=);
};


vector<triple> subset_sums(const vector<triple>& items)
{
    const size_t n = items.size();
    vector<triple> result;
    for(size_t mask = 0; mask < (1u << n); mask++)
    {
        triple curr = {0, 0, 0};
        for(size_t i = 0; i < n; i++)
            if(mask >> i & 1)
                curr += items[i];
        result.push_back(curr);
    }
    return result;
}

constexpr size_t lsb(size_t x) { return x & -x; }

size_t inner_nax;

struct dfenwick_tree
{
    size_t n;
    vector<int> F;
    dfenwick_tree(size_t _n) : n(_n), F(n+1, INT_MIN) {}
    int get_prefix(size_t p)
    {
        int r = INT_MIN;
        while(p)
            r = max(r, F[p]), p -= lsb(p);
        return r;
    }
    void set(size_t p, int v)
    {
        p++;
        while(p <= n)
            F[p] = max(F[p], v), p += lsb(p);
    }
};

int brute(vector<triple> items)
{
    int result = 0;
    for(auto sub : subset_sums(items))
    {
        if(sub.first >= sub.second and sub.second >= sub.third)
            result = max(result, sub.first);
    }
    return result;
}

int solve(vector<triple> items)
{
    const size_t n = items.size();
    vector<triple> space_half(items.begin(), items.begin() + n/2),
                   running_half(items.begin() + n/2, items.end());

    auto space = subset_sums(space_half), running = subset_sums(running_half);

    dfenwick_tree T(2 * (space.size() + running.size()));
    T.F.reserve(1 << 23);

    vector<int> toscale;
    unordered_map<int, size_t> scaler;
    scaler.reserve(1 << 22);

    vector<tuple<int, int, int>> qq;

    int result = 0;

    for(auto sub : space)
    {
        int x = sub.second - sub.first, y = sub.third - sub.second;
        qq.emplace_back(x, y, sub.first);
        toscale.push_back(y);

        if(sub.first >= sub.second and sub.second >= sub.third)
            result = max(result, sub.first);
    }

    for(auto sub : running)
    {
        int y = sub.second - sub.third;
        toscale.push_back(y);

        if(sub.first >= sub.second and sub.second >= sub.third)
            result = max(result, sub.first);
    }

    sort(toscale.begin(), toscale.end());
    for(size_t i = 0, f = 0; i < toscale.size(); i++)
    {
        if(i and toscale[i] != toscale[i-1])
            f++;
        scaler[toscale[i]] = f;
    }

    sort(qq.rbegin(), qq.rend());

    sort(running.begin(), running.end(), [&](const triple& a, const triple& b) {
        return a.first - a.second < b.first - b.second;
    });

    for(auto sub : running)
    {
        int x = sub.first - sub.second, y = sub.second - sub.third;

        while(not qq.empty() and get<0>(qq.back()) <= x)
        {
            int x1, y1, v; tie(x1, y1, v) = qq.back();
            T.set(scaler[y1], v);
            qq.pop_back();
        }

        result = max(result, sub.first + T.get_prefix(scaler[y] + 1));
    }

    return result;
}

int main()
{
    size_t n;
    cin >> n;

    vector<triple> items(n);

    for(size_t i = 0; i < n; i++)
    {
        cin >> items[i].first >> items[i].second >> items[i].third;
    }

    auto result = solve(items);
    cout << result << endl;

#ifdef XHOVA
    if(n <= 20)
    {
        cout << "? " << brute(items) << endl;
        auto bresult = brute(items);
        if(result != bresult)
        {
            for(auto it : items)
                cout << it.first << " " << it.second << " " << it.third << endl;
        }
        assert(result == bresult);
    }
#endif

}
