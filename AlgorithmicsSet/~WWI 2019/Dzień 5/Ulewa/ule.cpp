#include <bits/stdc++.h>

using namespace std;

struct mega_disjoint_set
{
    vector<size_t> parent, size_a;
    vector<uint> level_a, min_a, max_a;
    mega_disjoint_set(size_t n) : parent(n), size_a(n, 1), level_a(n), min_a(n), max_a(n)
    {
        iota(parent.begin(), parent.end(), 0);
        iota(min_a.begin(), min_a.end(), 0);
        iota(max_a.begin(), max_a.end(), 0);
    }

    size_t find(size_t v)
    {
        return parent[v] == v ? v : parent[v] = find(parent[v]);
    }

 size_t&  size(size_t v) { return  size_a[find(v)]; }
   uint& level(size_t v) { return level_a[find(v)]; }
   uint&   min(size_t v) { return   min_a[find(v)]; }
   uint&   max(size_t v) { return   max_a[find(v)]; }

    bool unite(size_t u, size_t v)
    {
        if((u = find(u)) == (v = find(v)))
            return false;
        if(size_a[u] > size_a[v])
            swap(u, v);
        size_a[v] += size_a[u];
        min_a[v] = std::min(min_a[v], min_a[u]);
        max_a[v] = std::max(max_a[v], max_a[u]);
        parent[u] = v;
        return true;
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, s;
    cin >> n >> s;

    if(n == 1)
    {
        cout << 0;
        return 0;
    }

    vector<uint> H(n+2);
    H[0] = H[n+1] = 1e9 + 7;
    for(size_t i = 1; i <= n; i++)
        cin >> H[i];

    vector<uint64_t> T(n + 2, SIZE_MAX);
    mega_disjoint_set S(n + 2);

    T[s] = 0;
    for(size_t i = 0; i <= n+1; i++)
        S.level(i) = H[i];

    function<void(size_t)> maybe_merge = [&](size_t i) {
        bool change = false;
        if(S.level(i) == S.level(S.min(i) - 1))
            if(S.unite(i, S.min(i) - 1))
                change = true;
        if(S.level(i) == S.level(S.max(i) + 1))
            if(S.unite(i, S.max(i) + 1))
                change = true;
        if(change)
            maybe_merge(i);
    };

    for(size_t i = 1; i <= n; i++)
        maybe_merge(i);


    size_t left = s, right = s;
    uint64_t the_clock, time_delta;

    auto fix_leaks = [&]() {
        while(S.level(right) >= S.level(right + 1))
            T[++right] = the_clock;
        while(S.level(left) >= S.level(left - 1))
            T[--left] = the_clock;
    };

    the_clock = 0;
    fix_leaks();

    auto delta_to_change = [&](size_t i) {
        return min(S.level(S.min(i) - 1), S.level(S.max(i) + 1)) - S.level(i);
    };

    uint64_t buffer = 0, buffer_left = 0, buffer_right = 0;
    for(; S.size(s) < n; the_clock += time_delta, buffer += 2 * time_delta)
    {
        bool extend_left = false, extend_here = false, extend_right = false;
        time_delta = UINT64_MAX;
        if(S.find(s) == S.find(left) and S.find(s) == S.find(right))
        {
            uint64_t target = delta_to_change(s);
            if(buffer >= 2*target*S.size(s))
            {
                buffer -= 2*target*S.size(s);
                S.level(s) += target;
                maybe_merge(s);
                extend_here = true;
            }
            else
                time_delta = (2*target*S.size(s) - buffer) / 2;
        }
        else
        {
            int rf = (S.find(s) != S.find(right)), lf = (S.find(s) != S.find(left));
            if(lf)
            {
                uint64_t target = delta_to_change(left);
                buffer_left += buffer / (lf + rf);
                if(buffer_left >= 2*target*S.size(left))
                {
                    buffer_left -= 2*target*S.size(left);
                    S.level(left) += target;
                    maybe_merge(left);
                    extend_left = true;
                }
                else
                    time_delta = min(time_delta, (lf + rf) * (2*target*S.size(left) - buffer_left) / 2);
            }
            if(rf)
            {
                uint64_t target = delta_to_change(right);
                buffer_right += buffer / (lf + rf);

                if(buffer_right >= 2*target*S.size(right))
                {
                    buffer_right -= 2*target*S.size(right);
                    S.level(right) += target;
                    maybe_merge(right);
                    extend_right = true;
                }
                else
                    time_delta = min(time_delta, (lf + rf) * (2*target*S.size(right) - buffer_right) / 2);
            }

            buffer = 0;
        }

        if(extend_here or extend_left or extend_right)
            time_delta = 0;

        fix_leaks();
    }


    for(size_t i = 1; i <= n; i++)
        cout << T[i] << " ";
}
